read -p "Enter the word to delete: " word
read -p "Enter the file names (separated by spaces): " files

for file in $files; do
    sed -i '' "/$word/d" "$file"
done