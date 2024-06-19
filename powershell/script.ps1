function Encrypt-Text {
    param (
        [string]$text,
        [int]$shift
    )
    
    $encryptedText = ""
    foreach ($char in $text.ToCharArray()) {
        if ($char -cmatch '[A-Za-z]') {
            $asciiVal = [int][char]$char
            if ($char -cmatch '[A-Z]') {
                $encryptedAsciiVal = ((($asciiVal - 65 + $shift) % 26) + 65)
            } else {
                $encryptedAsciiVal = ((($asciiVal - 97 + $shift) % 26) + 97)
            }
            $encryptedText += [char]$encryptedAsciiVal
        } else {
            $encryptedText += $char
        }
    }
    return $encryptedText
}

function Decrypt-Text {
    param (
        [string]$text,
        [int]$shift
    )
    
    $decryptedText = ""
    foreach ($char in $text.ToCharArray()) {
        if ($char -cmatch '[A-Za-z]') {
            $asciiVal = [int][char]$char
            if ($char -cmatch '[A-Z]') {
                $decryptedAsciiVal = ((($asciiVal - 65 - $shift + 26) % 26) + 65)
            } else {
                $decryptedAsciiVal = ((($asciiVal - 97 - $shift + 26) % 26) + 97)
            }
            $decryptedText += [char]$decryptedAsciiVal
        } else {
            $decryptedText += $char
        }
    }
    return $decryptedText
}

function Main {
    Clear-Host
    Write-Host "========================"
    Write-Host "  Witaj w szyfrze Cezara!  "
    Write-Host "========================"
    while ($true) {
        Write-Host "Wybierz opcje:"
        Write-Host "1. Zaszyfruj"
        Write-Host "2. Odszyfruj"
        Write-Host "3. Zakoncz"
        $choice = Read-Host "Wpisz swoj wybor"

        switch ($choice) {
            1 {
                $text = Read-Host "*Wpisz tekst do zaszyfrowania:"
                $shift = [int](Read-Host "*Wpisz wartosc przesuniecia:")
                $encrypted = Encrypt-Text -text $text -shift $shift
                Write-Host "#Zaszyfrowany tekst": $encrypted
            }
            2 {
                $text = Read-Host "*Wpisz tekst do odszyfrowania:"
                $shift = [int](Read-Host "*Wpisz wartosc przesuniecia:")
                $decrypted = Decrypt-Text -text $text -shift $shift
                Write-Host "#Odszyfrowany tekst": $decrypted
            }
            3 {
                Write-Host "Wyjscie..."
                exit
            }
            default {
                Write-Host "Nieprawidłowy wybor!"
            }
        }
    }
}

Main
