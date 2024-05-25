#!/bin/bash

# Function to encrypt text using Caesar Cipher
encrypt() {
    local text="$1"
    local shift="$2"
    local encrypted_text=""

    for (( i=0; i<${#text}; i++ )); do
        char="${text:$i:1}"
        if [[ $char =~ [A-Za-z] ]]; then
            ascii_val=$(printf "%d" "'$char")
            if [[ $char =~ [A-Z] ]]; then
                encrypted_ascii_val=$(( (ascii_val - 65 + shift) % 26 + 65 ))
            else
                encrypted_ascii_val=$(( (ascii_val - 97 + shift) % 26 + 97 ))
            fi
            encrypted_text+=$(printf "\\$(printf %o "$encrypted_ascii_val")")
        else
            encrypted_text+="$char"
        fi
    done

    echo "$encrypted_text"
}

# Function to decrypt text using Caesar Cipher
decrypt() {
    local text="$1"
    local shift="$2"
    local decrypted_text=""

    for (( i=0; i<${#text}; i++ )); do
        char="${text:$i:1}"
        if [[ $char =~ [A-Za-z] ]]; then
            ascii_val=$(printf "%d" "'$char")
            if [[ $char =~ [A-Z] ]]; then
                decrypted_ascii_val=$(( (ascii_val - 65 - shift + 26) % 26 + 65 ))
            else
                decrypted_ascii_val=$(( (ascii_val - 97 - shift + 26) % 26 + 97 ))
            fi
            decrypted_text+=$(printf "\\$(printf %o "$decrypted_ascii_val")")
        else
            decrypted_text+="$char"
        fi
    done

    echo "$decrypted_text"
}

# Main function
main() {
    clear
    echo "========================"
    echo "  Welcome to Caesar Cipher!  "
    echo "========================"
    while true; do
        echo "Choose an option:"
        echo "1. Encrypt"
        echo "2. Decrypt"
        echo "3. Exit"
        read -p "Enter your choice: " choice

        case $choice in
            1)
                read -p "Enter text to encrypt: " text
                read -p "Enter shift value: " shift
                encrypted=$(encrypt "$text" "$shift")
                echo "Encrypted text: $encrypted"
                ;;
            2)
                read -p "Enter text to decrypt: " text
                read -p "Enter shift value: " shift
                decrypted=$(decrypt "$text" "$shift")
                echo "Decrypted text: $decrypted"
                ;;
            3)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid choice!"
                ;;
        esac
    done
}

# Run the main function
main
