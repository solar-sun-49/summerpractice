import base64, json, hmac, hashlib

token = "eyJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoiZ3Vlc3QiLCJyb2xlIjoidXNlciJ9.SIGNATURE"

# --- Decode ---
parts = token.split(".")
header  = json.loads(base64.urlsafe_b64decode(parts[0] + "=="))
payload = json.loads(base64.urlsafe_b64decode(parts[1] + "=="))

print("Original payload:", payload)

# --- Modify role ---
payload["role"] = "admin"

# --- Re-encode header and payload ---
def b64_encode(data: dict) -> str:
    return base64.urlsafe_b64encode(
        json.dumps(data, separators=(",", ":")).encode()
    ).rstrip(b"=").decode()

new_header  = b64_encode(header)
new_payload = b64_encode(payload)
unsigned_token = f"{new_header}.{new_payload}"

print("Modified payload:", payload)
print("\nUnsigned token (needs valid signature):")
print(f"{unsigned_token}.<SIGNATURE>")

# --- Sign with known secret (if you have it) ---
secret = b"your-secret-key"   # replace with actual secret
sig = hmac.new(secret, unsigned_token.encode(), hashlib.sha256).digest()
signature = base64.urlsafe_b64encode(sig).rstrip(b"=").decode()

print("\nSigned token:")
print(f"{unsigned_token}.{signature}")