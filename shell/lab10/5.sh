read -p "Enter file 1 : " file1
read -p "Enter file 2 : " file2

if diff -q "$file1" "$file2" > /dev/null; then
    rm "$file2"
    echo "Duplicate file deleted successfully"
else
    echo "No duplicate file found"
fi