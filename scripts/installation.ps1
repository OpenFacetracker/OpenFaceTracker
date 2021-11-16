#   This script is part of OpenFaceTracker project
#
#   Software Developer :        Tony DELHOMMAIS 
#   Project Manager :           Richard REY
#   Date :                      5th June 2020
#   Version :                   6.0.0
#   Copyright (C) :             Laboratoire CNS/(C+V)
#                               ESIEA - Laval 2020
#
#   This text plain is developed in the hope that it will be useful
#   but WITHOUT ANY WARRANTY ; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

function Show-Message {

    param (
        [string]$Message = "Veuillez entrer votre message",
        [string]$Titre = "Titre de la fenêtre",
        [switch]$OKCancel,
        [switch]$AbortRetryIgnore,
        [switch]$YesNoCancel,
        [switch]$YesNo,
        [switch]$RetryCancel,
        [switch]$IconErreur,
        [switch]$IconQuestion,
        [switch]$IconAvertissement,
        [switch]$IconInformation
    )

    # Affecter la valeur selon le type de boutons choisis
    if ($OKCancel) { $Btn = 1 }
    elseif ($AbortRetryIgnore) { $Btn = 2 }
    elseif ($YesNoCancel) { $Btn = 3 }
    elseif ($YesNo) { $Btn = 4 }
    elseif ($RetryCancel) { $Btn = 5 }
    else { $Btn = 0 }
    
    # Affecter la valeur pour l'icone 
    if ($IconErreur) {$Icon = 16 }
    elseif ($IconQuestion) {$Icon = 32 }
    elseif ($IconAvertissement) {$Icon = 48 }
    elseif ($IconInformation) {$Icon = 64 }
    else {$Icon = 0 }
    

    # Charger la bibliothèque d'objets graphiques Windows.Forms
    [System.Reflection.Assembly]::LoadWithPartialName("System.Windows.Forms") | Out-Null

    # Afficher la boite de dialogue et renvoyer la valeur de retour (bouton appuyé)
    $Reponse = [System.Windows.Forms.MessageBox]::Show($Message, $Titre , $Btn, $Icon)
    Return $Reponse
}

function Test-Administrator
{
    [OutputType([bool])]
    param()
    process {
        [Security.Principal.WindowsPrincipal]$user = [Security.Principal.WindowsIdentity]::GetCurrent();
        return $user.IsInRole([Security.Principal.WindowsBuiltinRole]::Administrator);
    }
}

if(-not (Test-Administrator))
{
    start-process -Verb Runas -FilePath "Powershell.exe" -ArgumentList "-file $PSCommandPath -ExecutionPolicy Bypass"

    exit 1;
}

# Definition of variables for the files CONTROL and portfile.cmake
$Control = "Source: cppdb
Version: 0.3.1
Description: cppdb lib for database in Cpp
"

$Portfile = "vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO melpon/cppdb
    REF v0.3.1
    SHA512 d45b262a64549306229963291a2a51b1233ba88d8f7203dcb0ff1b593d5ba035905a895cc495eee6fdccddc35653bee2aa0a85ef05e47182f6af02740208aa0f
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH `$`{SOURCE_PATH`}
    PREFER_NINJA
)

vcpkg_install_cmake()
file(INSTALL `$`{SOURCE_PATH`}/copyright.txt DESTINATION `$`{CURRENT_PACKAGES_DIR`}/share/cppdb RENAME copyright)
file(REMOVE_RECURSE `"`$`{CURRENT_PACKAGES_DIR`}/debug/include`")"

# List of the differents packages to install
$PackagesToInstall =  "opencv",
                      "opencv4[contrib]",
                      "opencv4[ffmpeg]",
                      "curl",
                      "json-c",
                      "sqlite3[tool]",
                      "cppdb",
                      "nlohmann-json",
                      "boost"

# Check if system architecture is 64 bits or other and create a environement variable to store it
if([Environment]::Is64BitProcess) {
    [System.Environment]::SetEnvironmentVariable('VCPKG_DEFAULT_TRIPLET','x64-windows',[System.EnvironmentVariableTarget]::Machine)
	$env:VCPKG_DEFAULT_TRIPLET = 'x64-windows'
}
else {
    [System.Environment]::SetEnvironmentVariable('VCPKG_DEFAULT_TRIPLET','x86-windows',[System.EnvironmentVariableTarget]::Machine)
	$env:VCPKG_DEFAULT_TRIPLET = 'x86-windows'
}

# Get the first 3 letters of the environement variable created for after
$Xxx = $env:VCPKG_DEFAULT_TRIPLET.SubString(0, 3).ToUpper()

#   Display Welcome message
Write-Output "OpenFaceTracker For Developers"
Write-Output "GNU GPL Version 5.0.0"
Write-Output "© Copyright - ESIEA Campus Laval 2019"
Write-Output "CNS (Confiance Numérique et Sécurité)\n"
Write-Output "Starting the configuration of your Windows Operating System"
Write-Output ""
Write-Output "Make sure Microsoft Visual Studio is installed with the 'C++ Desktop Development' workload and the English language module before start the installation script"
Write-Output ""

# Vcpkg directory
#$DirectoryPath = "$env:USERPROFILE\vcpkg"
$DirectoryPath = "C:\dev\vcpkg"

# Check if vcpkg directory already exist and create it if isin't
if(Test-Path $DirectoryPath -PathType Container) {
    Write-Output "Directory `"$DirectoryPath`" already exist"
}
else {
    mkdir $DirectoryPath
    Write-Output "Directory `"$DirectoryPath`" was created"
}
Write-Output ""

# Check if vcpkg has been installed
if(Test-Path "$DirectoryPath\vcpkg.exe" -PathType Leaf) {
    Write-Output "Vcpkg has been installed"
}
else {
    Write-Output "Vcpkg insn't installed"
    Write-Output ""

    # Check if installer is downloaded
    if(Test-Path "$DirectoryPath\scripts\bootstrap.ps1" -PathType Leaf) {
        Write-Output "Vcpkg is already downloaded"
    }
    else {
        Write-Output "Vcpkg is not already downloaded"
        Write-Output ""

        # Clear the directory
        rm -Recurse $DirectoryPath/*

        $url = "https://github.com/microsoft/vcpkg/archive/master.zip"
        $output = "$DirectoryPath\master.zip"

        # Dwnload the archive file of vcpkg
        Write-Output "Downloading vcpkg from $url ..."
        $start_time_download_vcpkg = Get-Date
        (New-Object System.Net.WebClient).DownloadFile($url, $output)

        Write-Output "Download done in $((Get-Date).Subtract($start_time_download_vcpkg).Seconds) second(s)"

        Write-Output ""

        # Extract vcpkg's files from archive
        Write-Output "Extracting file from archive ..."
        Expand-Archive -LiteralPath $output -DestinationPath $DirectoryPath
        Write-Output "Extract done"

        rm -Recurse $output

        $FileName = Get-ChildItem -Path $DirectoryPath -Name

        # Move vcpkg's files to the directory path
        move $DirectoryPath/$FileName/* $DirectoryPath/

        rm -Recurse $DirectoryPath/$FileName
    }
    Write-Output ""

    Write-Output "Installation of vcpkg ..."

    ADD-content -path "$DirectoryPath/scripts/bootstrap.ps1" -value "exit 0"

    # Start the installation of vcpkg
    $InstallVcpkg = (start-process -FilePath "Powershell.exe" -ArgumentList "-File $DirectoryPath/scripts/bootstrap.ps1" -Wait -NoNewWindow -PassThru)

    # If an error occurred during installation
    if($InstallVcpkg.ExitCode -ne 0) {
        Show-Message -Message "Microsoft Visual Studio installer will start. Make sure to install 'C++ Desktop Development' workload and the English language module then close all Visual Studio Window" -Titre "Visual Studio installer" -IconInformation
        Write-Output "Microsoft Visual Studio installer will start. Make sure to install 'C++ Desktop Development' workload and the English language module then close all Visual Studio Window"

        $url = "https://download.visualstudio.microsoft.com/download/pr/9fcc1f0c-c63f-4424-bc46-7351a59fba06/1ed7863dc633c57c42a88c5cef907048/vs_community.exe"
        $output = "$DirectoryPath\setup_vs.exe"
                (New-Object System.Net.WebClient).DownloadFile($url, $output)
        
        if(Test-Path "$output" -PathType Leaf)
        {
            start-process -FilePath $output -ArgumentList "--install --addProductLang en-US
            --add Microsoft.VisualStudio.ComponentGroup.NativeDesktop.Core
            --add Microsoft.VisualStudio.Component.IntelliCode
            --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64
            --add Microsoft.VisualStudio.Component.Windows10SDK.18362
            --add Microsoft.VisualStudio.Component.Debugger.JustInTime
            --add Microsoft.VisualStudio.Component.VC.DiagnosticTools
            --add Microsoft.VisualStudio.Component.VC.CMake.Project
            --add Microsoft.VisualStudio.Component.VC.ATL
            --add Microsoft.VisualStudio.Component.VC.TestAdapterForBoostTest
            --add Microsoft.VisualStudio.Component.VC.TestAdapterForGoogleTest
            --add Component.Microsoft.VisualStudio.LiveShare
            --add Microsoft. VisualStudio. Component. VC. ASAN" -Wait
            $InstallVcpkg = (start-process -FilePath "Powershell.exe" -ArgumentList "-File $DirectoryPath/scripts/bootstrap.ps1" -Wait -NoNewWindow -PassThru)
        }
    }

    Write-Output "Installation done"
}
Write-Output ""


# Creation of files for cppdb installation
Write-Output "Creation of files for cppdb installation ..."

$CppdbPortDirectoryPath = "$DirectoryPath/ports/cppdb"

# Check if cppdb installation folder exist
if(Test-Path $CppdbPortDirectoryPath -PathType Container) {
    # Clean the folder
    rm -Recurse $CppdbPortDirectoryPath/*
}
else {
    # Create the folder
    mkdir $CppdbPortDirectoryPath
}

New-Item -Path . -Name "CONTROL" -ItemType File

New-Item -Path . -Name "portfile.cmake" -ItemType File

Set-Content -Path "$CppdbPortDirectoryPath/CONTROL" -Value $Control

Set-Content -Path "$CppdbPortDirectoryPath/portfile.cmake" -Value $Portfile

Write-Output "Creation done"
Write-Output ""

# Install all the differents packages
Write-Output "Installation of this packages and their dependencies :"
Write-Output $PackagesToInstall
Write-Output ""

foreach($Package in $PackagesToInstall) {
    start-process -FilePath "$DirectoryPath/vcpkg.exe" -ArgumentList "install $Package --recurse" -NoNewWindow -Wait
}

# Installation of youtube-dl from ()
Invoke-WebRequest -Uri "https://yt-dl.org/downloads/2020.07.28/youtube-dl.exe" -OutFile "$DirectoryPath/installed/$env:VCPKG_DEFAULT_TRIPLET/tools/youtube-dl.exe"

Write-Output "Installation done"
Write-Output ""

Write-Output "Move the 'cppdb_sqlite3.dll' file to his good location"
Write-Output ""
 
Copy-Item -Path $DirectoryPath\packages\cppdb_$env:VCPKG_DEFAULT_TRIPLET\bin\cppdb_sqlite3.dll -Destination $DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\tools\

Write-Output "Create all the differents environments variables"
Write-Output ""

[System.Environment]::SetEnvironmentVariable("VCPKG_ROOT","$DirectoryPath",[System.EnvironmentVariableTarget]::Machine)
[System.Environment]::SetEnvironmentVariable("VCPKG_INCLUDE_$Xxx","$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\include\",[System.EnvironmentVariableTarget]::Machine)
[System.Environment]::SetEnvironmentVariable("VCPKG_LIB_$Xxx","$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\lib\",[System.EnvironmentVariableTarget]::Machine)

$Old_Path=(Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name Path).Path
if($Old_Path -notlike "*$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\tools\*") {
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH -Value ($Old_Path += ";$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\tools\")
}

$Old_Path=(Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name Path).Path
if($Old_Path -notlike "*$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\bin\*") {
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH -Value ($Old_Path += ";$DirectoryPath\installed\$env:VCPKG_DEFAULT_TRIPLET\bin\")
}

Write-Output "Configuration done"
exit
