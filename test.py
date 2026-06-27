#!/usr/bin/env python3
"""
ECB Byte-at-a-Time Oracle Attack
Leaks a secret suffix appended by the server before encryption.
"""

import requests
import base64
import json

TARGET_URL = "http://challenge.erakshak.nexus-svnit.in:5001/encrypt"  # <-- change this

def encrypt(prefix_bytes: bytes) -> bytes:
    """Send prefix to oracle, get back ciphertext."""
    b64 = base64.b64encode(prefix_bytes).decode()
    resp = requests.post(TARGET_URL, json={"input": b64})
    resp.raise_for_status()
    data = resp.json()
    # Adjust key name if the response uses a different field
    ct_b64 = data.get("ciphertext") or data.get("result") or data.get("output")
    return base64.b64decode(ct_b64)

def detect_block_size() -> int:
    """Detect block size by growing input until ciphertext length jumps."""
    baseline = len(encrypt(b"A"))
    for i in range(2, 64):
        ct = encrypt(b"A" * i)
        if len(ct) != baseline:
            return len(ct) - baseline
    raise RuntimeError("Could not detect block size")

def detect_prefix_len(block_size: int) -> int:
    """
    Detect any fixed server-side prefix before our input.
    (If there's none, this returns 0.)
    """
    # Send two different 2-block payloads; find first differing block
    for pad in range(block_size):
        ct1 = encrypt(bytes([0x41] * (pad + block_size * 2)))
        ct2 = encrypt(bytes([0x42] * (pad + block_size * 2)))
        blocks1 = [ct1[i:i+block_size] for i in range(0, len(ct1), block_size)]
        blocks2 = [ct2[i:i+block_size] for i in range(0, len(ct2), block_size)]
        for idx, (b1, b2) in enumerate(zip(blocks1, blocks2)):
            if b1 == b2:
                # This block is identical => it's a fixed prefix block
                continue
            else:
                # First differing block is where our input starts
                prefix_blocks = idx
                prefix_len = prefix_blocks * block_size - pad
                return max(0, prefix_len)
    return 0

def ecb_byte_at_a_time() -> bytes:
    print("[*] Detecting block size...")
    block_size = detect_block_size()
    print(f"    Block size: {block_size}")

    print("[*] Detecting server prefix length...")
    prefix_len = detect_prefix_len(block_size)
    print(f"    Server prefix length: {prefix_len}")

    # Pad to align our input to a block boundary after the server prefix
    prefix_pad = (block_size - (prefix_len % block_size)) % block_size
    prefix_blocks = (prefix_len + prefix_pad) // block_size

    print("[*] Leaking secret byte by byte...\n")
    recovered = b""

    while True:
        # Number of 'A' bytes to push the next unknown byte to end of a block
        pad_len = prefix_pad + (block_size - 1 - (len(recovered) % block_size))
        padding = b"A" * pad_len

        # The target block index containing the unknown byte
        target_block_idx = prefix_blocks + (len(recovered) // block_size)

        # Get the reference ciphertext
        reference = encrypt(padding)
        target_block = reference[target_block_idx * block_size:(target_block_idx + 1) * block_size]

        # Brute-force the unknown byte
        found = False
        for candidate in range(256):
            # Build a full block: padding + already recovered + candidate
            test_input = padding + recovered + bytes([candidate])
            # We only need the block at target_block_idx
            ct = encrypt(test_input)
            test_block = ct[target_block_idx * block_size:(target_block_idx + 1) * block_size]

            if test_block == target_block:
                recovered += bytes([candidate])
                char = chr(candidate) if 32 <= candidate < 127 else f"\\x{candidate:02x}"
                print(f"    Byte {len(recovered):>3}: 0x{candidate:02x}  '{char}'  => {recovered.decode('latin1')}")
                found = True
                break

        if not found:
            print("\n[!] Could not find next byte — likely hit padding or end of secret.")
            break

    return recovered

if __name__ == "__main__":
    print("=" * 55)
    print("  ECB Byte-at-a-Time Oracle Attack")
    print("=" * 55)
    secret = ecb_byte_at_a_time()
    print(f"\n[+] Recovered secret:\n    {secret.decode('latin1', errors='replace')}")