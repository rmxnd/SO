#!/usr/bin/env bash
# https://privacy.sexy — v0.13.0 — Fri, 08 Mar 2024 18:27:18 GMT
if [ "$EUID" -ne 0 ]; then
  script_path=$([[ "$0" = /* ]] && echo "$0" || echo "$PWD/${0#./}")
  sudo "$script_path" || (
    echo 'Administrator privileges are required.'
    exit 1
  )
  exit 0
fi
export HOME="/home/${SUDO_USER:-${USER}}" # Keep `~` and `$HOME` for user not `/root`.


# ----------------------------------------------------------
# ------------Clear privacy.sexy script history-------------
# ----------------------------------------------------------
echo '--- Clear privacy.sexy script history'
# Clear directory contents: "$HOME/.config/privacy.sexy/runs"
glob_pattern="$HOME/.config/privacy.sexy/runs/*"
rm -rfv $glob_pattern
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear privacy.sexy activity logs-------------
# ----------------------------------------------------------
echo '--- Clear privacy.sexy activity logs'
# Clear directory contents: "$HOME/.config/privacy.sexy/logs"
glob_pattern="$HOME/.config/privacy.sexy/logs/*"
rm -rfv $glob_pattern
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------------Clear Wine cache---------------------
# ----------------------------------------------------------
echo '--- Clear Wine cache'
# Temporary Windows files for global prefix
rm -rfv ~/.wine/drive_c/windows/temp/*
# Wine cache:
rm -rfv ~/.cache/wine/
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------------Clear Winetricks cache------------------
# ----------------------------------------------------------
echo '--- Clear Winetricks cache'
rm -rfv ~/.cache/winetricks/
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------Clear Thunderbird personal address book----------
# ----------------------------------------------------------
echo '--- Clear Thunderbird personal address book'
# abook.sqlite: Global installation
rm -fv ~/.thunderbird/*/abook.sqlite
# abook.sqlite: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/abook.sqlite
# abook.sqlite: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/abook.sqlite
# abook.sqlite-wal: Global installation
rm -fv ~/.thunderbird/*/abook.sqlite-wal
# abook.sqlite-wal: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/abook.sqlite-wal
# abook.sqlite-wal: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/abook.sqlite-wal
# abook.mab: Global installation
rm -fv ~/.thunderbird/*/abook.mab
# abook.mab: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/abook.mab
# abook.mab: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/abook.mab
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------Clear Thunderbird collected address book---------
# ----------------------------------------------------------
echo '--- Clear Thunderbird collected address book'
# history.sqlite: Global installation
rm -fv ~/.thunderbird/*/history.sqlite
# history.sqlite: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/history.sqlite
# history.sqlite: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/history.sqlite
# history.sqlite-wal: Global installation
rm -fv ~/.thunderbird/*/history.sqlite-wal
# history.sqlite-wal: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/history.sqlite-wal
# history.sqlite-wal: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/history.sqlite-wal
# history.mab: Global installation
rm -fv ~/.thunderbird/*/history.mab
# history.mab: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/history.mab
# history.mab: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/history.mab
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------------Clear Thunderbird cookies-----------------
# ----------------------------------------------------------
echo '--- Clear Thunderbird cookies'
# cookies.sqlite: Global installation
rm -fv ~/.thunderbird/*/cookies.sqlite
# cookies.sqlite: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/cookies.sqlite
# cookies.sqlite: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/cookies.sqlite
# cookies.sqlite-wal: Global installation
rm -fv ~/.thunderbird/*/cookies.sqlite-wal
# cookies.sqlite-wal: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/cookies.sqlite-wal
# cookies.sqlite-wal: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/cookies.sqlite-wal
# cookies.sqlite-journal: Global installation
rm -fv ~/.thunderbird/*/cookies.sqlite-journal
# cookies.sqlite-journal: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/cookies.sqlite-journal
# cookies.sqlite-journal: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/cookies.sqlite-journal
# cookies.sqlite-shm: Global installation
rm -fv ~/.thunderbird/*/cookies.sqlite-shm
# cookies.sqlite-shm: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/cookies.sqlite-shm
# cookies.sqlite-shm: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/cookies.sqlite-shm
# ----------------------------------------------------------


# Clear Thunderbird session restoration data (open windows and tabs)
echo '--- Clear Thunderbird session restoration data (open windows and tabs)'
# session.json: Global installation
rm -fv ~/.thunderbird/*/session.json
# session.json: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/session.json
# session.json: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/session.json
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Clear Thunderbird passwords----------------
# ----------------------------------------------------------
echo '--- Clear Thunderbird passwords'
# logins.json: Global installation
rm -fv ~/.thunderbird/*/logins.json
# logins.json: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/logins.json
# logins.json: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/logins.json
# logins-backup.json: Global installation
rm -fv ~/.thunderbird/*/logins-backup.json
# logins-backup.json: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/logins-backup.json
# logins-backup.json: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/logins-backup.json
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------Clear Thunderbird download history------------
# ----------------------------------------------------------
echo '--- Clear Thunderbird download history'
# downloads.rdf: Global installation
rm -fv ~/.thunderbird/*/downloads.rdf
# downloads.rdf: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/downloads.rdf
# downloads.rdf: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/downloads.rdf
# downloads.sqlite: Global installation
rm -fv ~/.thunderbird/*/downloads.sqlite
# downloads.sqlite: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/downloads.sqlite
# downloads.sqlite: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/downloads.sqlite
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------Clear clicked links history in Thunderbird--------
# ----------------------------------------------------------
echo '--- Clear clicked links history in Thunderbird'
# places.sqlite: Global installation
rm -fv ~/.thunderbird/*/places.sqlite
# places.sqlite: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/places.sqlite
# places.sqlite: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/places.sqlite
# places.sqlite-shm: Global installation
rm -fv ~/.thunderbird/*/places.sqlite-shm
# places.sqlite-shm: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/places.sqlite-shm
# places.sqlite-shm: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/places.sqlite-shm
# places.sqlite.wal: Global installation
rm -fv ~/.thunderbird/*/places.sqlite.wal
# places.sqlite.wal: Flatpak installation
rm -fv ~/snap/thunderbird/common/.thunderbird/*/places.sqlite.wal
# places.sqlite.wal: Snap installation
rm -fv ~/.var/app/org.mozilla.Thunderbird/.thunderbird/*/places.sqlite.wal
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------Clear Visual Studio Code crash reports----------
# ----------------------------------------------------------
echo '--- Clear Visual Studio Code crash reports'
# Crash\ Reports: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/Crash\ Reports/*
# Crash\ Reports: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/Crash\ Reports/*
# exthost\ Crash\ Reports: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/exthost\ Crash\ Reports/*
# exthost\ Crash\ Reports: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/exthost\ Crash\ Reports/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear Visual Studio Code cache--------------
# ----------------------------------------------------------
echo '--- Clear Visual Studio Code cache'
# Cache: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/Cache/*
# Cache: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/Cache/*
# CachedData: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/CachedData/*
# CachedData: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/CachedData/*
# Code\ Cache: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/Code\ Cache/*
# Code\ Cache: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/Code\ Cache/*
# GPUCache: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/GPUCache/*
# GPUCache: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/GPUCache/*
# CachedExtensions: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/CachedExtensions/*
# CachedExtensions: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/CachedExtensions/*
# CachedExtensionVSIXs: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/CachedExtensionVSIXs/*
# CachedExtensionVSIXs: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/CachedExtensionVSIXs/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear Visual Studio Code logs---------------
# ----------------------------------------------------------
echo '--- Clear Visual Studio Code logs'
# logs: Global installation (also Snap with --classic)
rm -rfv ~/.config/Code/logs/*
# logs: Flatpak installation
rm -rfv ~/.var/app/com.visualstudio.code/config/Code/logs/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear Azure CLI telemetry data--------------
# ----------------------------------------------------------
echo '--- Clear Azure CLI telemetry data'
rm -rfv ~/.azure/telemetry
rm -fv ~/.azure/telemetry.txt
rm -fv ~/.azure/logs/telemetry.txt
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------------Clear Azure CLI logs-------------------
# ----------------------------------------------------------
echo '--- Clear Azure CLI logs'
rm -rfv ~/.azure/logs
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------------Clear Azure CLI cache-------------------
# ----------------------------------------------------------
echo '--- Clear Azure CLI cache'
if ! command -v 'az' &> /dev/null; then
  echo 'Skipping because "az" is not found.'
else
  az cache purge
fi
# ----------------------------------------------------------


# Clear Azure login data (this will log you out of the current session)
echo '--- Clear Azure login data (this will log you out of the current session)'
if ! command -v 'az' &> /dev/null; then
  echo 'Skipping because "az" is not found.'
else
  az logout 2&> /dev/null
az account clear
rm -fv ~/.azure/accessTokens.json
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------------Clear Python history-------------------
# ----------------------------------------------------------
echo '--- Clear Python history'
rm -fv ~/.python_history
sudo rm -fv /root/.python_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear Steam cache---------------------
# ----------------------------------------------------------
echo '--- Clear Steam cache'
# Global installation
rm -rfv ~/.local/share/Steam/appcache/*
# Snap
rm -rfv ~/snap/steam/common/.cache/*
rm -rfv ~/snap/steam/common/.local/share/Steam/appcache/*
# Flatpak
rm -rfv ~/.var/app/com.valvesoftware.Steam/cache/*
rm -rfv ~/.var/app/com.valvesoftware.Steam/data/Steam/appcache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------------Clear Clementine cache------------------
# ----------------------------------------------------------
echo '--- Clear Clementine cache'
# Global installation
rm -rfv ~/.cache/Clementine/*
# Flatpak installation
rm -rfv ~/.var/app/org.clementine_player.Clementine/cache/*
# Snap installation
rm -rfv ~/snap/clementine/common/.cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear LibreOffice usage history--------------
# ----------------------------------------------------------
echo '--- Clear LibreOffice usage history'
# Global installation
rm -f ~/.config/libreoffice/4/user/registrymodifications.xcu
# Snap package
rm -fv ~/snap/libreoffice/*/.config/libreoffice/4/user/registrymodifications.xcu
# Flatpak installation
rm -fv ~/.var/app/org.libreoffice.LibreOffice/config/libreoffice/4/user/registrymodifications.xcu
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------------Clear user-specific cache-----------------
# ----------------------------------------------------------
echo '--- Clear user-specific cache'
rm -rfv ~/.cache/*
sudo rm -rfv root/.cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------------Clear system-wide cache------------------
# ----------------------------------------------------------
echo '--- Clear system-wide cache'
rm -rf /var/cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear Flatpak application cache--------------
# ----------------------------------------------------------
echo '--- Clear Flatpak application cache'
rm -rfv ~/.var/app/*/cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Clear Snap application cache---------------
# ----------------------------------------------------------
echo '--- Clear Snap application cache'
rm -fv ~/snap/*/*/.cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear thumbnails (icon cache)---------------
# ----------------------------------------------------------
echo '--- Clear thumbnails (icon cache)'
rm -rfv ~/.thumbnails/*
rm -rfv ~/.cache/thumbnails/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear global temporary folders--------------
# ----------------------------------------------------------
echo '--- Clear global temporary folders'
sudo rm -rfv /tmp/*
sudo rm -rfv /var/tmp/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear system crash report files--------------
# ----------------------------------------------------------
echo '--- Clear system crash report files'
sudo rm -rfv /var/crash/*
sudo rm -rfv /var/lib/systemd/coredump/
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear system logs (`journald`)--------------
# ----------------------------------------------------------
echo '--- Clear system logs (`journald`)'
if ! command -v 'journalctl' &> /dev/null; then
  echo 'Skipping because "journalctl" is not found.'
else
  sudo journalctl --vacuum-time=1s
fi
sudo rm -rfv /run/log/journal/*
sudo rm -rfv /var/log/journal/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Clear Zeitgeist data (activity logs)-----------
# ----------------------------------------------------------
echo '--- Clear Zeitgeist data (activity logs)'
sudo rm -rfv {/root,/home/*}/.local/share/zeitgeist
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------------------Empty trash------------------------
# ----------------------------------------------------------
echo '--- Empty trash'
# Empty global trash
rm -rfv ~/.local/share/Trash/*
sudo rm -rfv /root/.local/share/Trash/*
# Empty Snap trash
rm -rfv ~/snap/*/*/.local/share/Trash/*
# Empty Flatpak trash (apps may not choose to use Portal API)
rm -rfv ~/.var/app/*/data/Trash/*
# ----------------------------------------------------------


echo 'Your privacy and security is now hardened 🎉💪'
echo 'Press any key to exit.'
read -n 1 -s
