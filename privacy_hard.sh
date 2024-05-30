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
# --------------------Clear bash history--------------------
# ----------------------------------------------------------
echo '--- Clear bash history'
rm -fv ~/.bash_history
sudo rm -fv /root/.bash_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear Zsh history---------------------
# ----------------------------------------------------------
echo '--- Clear Zsh history'
rm -fv ~/.zsh_history
sudo rm -fv /root/.zsh_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear tcsh history--------------------
# ----------------------------------------------------------
echo '--- Clear tcsh history'
rm -fv ~/.history
sudo rm -fv /root/.history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear fish history--------------------
# ----------------------------------------------------------
echo '--- Clear fish history'
rm -fv ~/.local/share/fish/fish_history
sudo rm -fv /root/.local/share/fish/fish_history
rm -fv ~/.config/fish/fish_history
sudo rm -fv /root/.config/fish/fish_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Clear KornShell (ksh) history---------------
# ----------------------------------------------------------
echo '--- Clear KornShell (ksh) history'
rm -fv ~/.sh_history
sudo rm -fv /root/.sh_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear ash history---------------------
# ----------------------------------------------------------
echo '--- Clear ash history'
rm -fv ~/.ash_history
sudo rm -fv /root/.ash_history
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------------Clear crosh history--------------------
# ----------------------------------------------------------
echo '--- Clear crosh history'
rm -fv ~/.crosh_history
sudo rm -fv /root/.crosh_history
# ----------------------------------------------------------


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
# ------------Clear GTK recently used files list------------
# ----------------------------------------------------------
echo '--- Clear GTK recently used files list'
# From global installations
rm -fv /.recently-used.xbel
rm -fv ~/.local/share/recently-used.xbel*
# From snap packages
rm -fv ~/snap/*/*/.local/share/recently-used.xbel
# From Flatpak packages
rm -fv ~/.var/app/*/data/recently-used.xbel
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------Clear KDE-tracked recently used items list--------
# ----------------------------------------------------------
echo '--- Clear KDE-tracked recently used items list'
# From global installations
rm -rfv ~/.local/share/RecentDocuments/*.desktop
rm -rfv ~/.kde/share/apps/RecentDocuments/*.desktop
rm -rfv ~/.kde4/share/apps/RecentDocuments/*.desktop
# From snap packages
rm -fv ~/snap/*/*/.local/share/*.desktop
# From Flatpak packages
rm -rfv ~/.var/app/*/data/*.desktop
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------------Clear Snap cache---------------------
# ----------------------------------------------------------
echo '--- Clear Snap cache'
sudo rm -rfv /var/lib/snapd/cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------------Remove old Snap packages-----------------
# ----------------------------------------------------------
echo '--- Remove old Snap packages'
if ! command -v 'snap' &> /dev/null; then
  echo 'Skipping because "snap" is not found.'
else
  snap list --all | while read name version rev tracking publisher notes; do
  if [[ $notes = *disabled* ]]; then
    sudo snap remove "$name" --revision="$rev";
  fi
done
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Remove orphaned Flatpak runtimes-------------
# ----------------------------------------------------------
echo '--- Remove orphaned Flatpak runtimes'
if ! command -v 'flatpak' &> /dev/null; then
  echo 'Skipping because "flatpak" is not found.'
else
  flatpak uninstall --unused --noninteractive
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------------Clear Flatpak cache--------------------
# ----------------------------------------------------------
echo '--- Clear Flatpak cache'
# Temporary cache
sudo rm -rfv /var/tmp/flatpak-cache-*
# New cache
rm -rfv ~/.cache/flatpak/system-cache/*
# Old cache
rm -rfv ~/.local/share/flatpak/system-cache/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Clear obsolete APT packages----------------
# ----------------------------------------------------------
echo '--- Clear obsolete APT packages'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  sudo apt-get autoclean
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Clear APT package file lists---------------
# ----------------------------------------------------------
echo '--- Clear APT package file lists'
sudo rm -rfv /var/lib/apt/lists/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------Clear orphaned APT package dependencies----------
# ----------------------------------------------------------
echo '--- Clear orphaned APT package dependencies'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  sudo apt-get -y autoremove --purge
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Clear cache for APT packages---------------
# ----------------------------------------------------------
echo '--- Clear cache for APT packages'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  sudo apt-get clean
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear YUM/RPM data--------------------
# ----------------------------------------------------------
echo '--- Clear YUM/RPM data'
if ! command -v 'yum' &> /dev/null; then
  echo 'Skipping because "yum" is not found.'
else
  yum clean all --enablerepo='*'
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------------Clear DNF/RPM data--------------------
# ----------------------------------------------------------
echo '--- Clear DNF/RPM data'
if ! command -v 'dnf' &> /dev/null; then
  echo 'Skipping because "dnf" is not found.'
else
  dnf clean all --enablerepo='*'
fi
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


# ----------------------------------------------------------
# --------------Clear global temporary folders--------------
# ----------------------------------------------------------
echo '--- Clear global temporary folders'
sudo rm -rfv /tmp/*
sudo rm -rfv /var/tmp/*
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------Disable participation in Popularity Contest--------
# ----------------------------------------------------------
echo '--- Disable participation in Popularity Contest'
config_file='/etc/popularity-contest.conf'
if [ -f "$config_file" ]; then
  sudo sed -i '/PARTICIPATE/c\PARTICIPATE=no' "$config_file"
else
  echo "Skipping because configuration file at ($config_file) is not found. Is popcon installed?"
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------Remove Popularity Contest (`popcon`) package-------
# ----------------------------------------------------------
echo '--- Remove Popularity Contest (`popcon`) package'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  apt_package_name='popularity-contest'
if status="$(dpkg-query -W --showformat='${db:Status-Status}' "$apt_package_name" 2>&1)" \
    && [ "$status" = installed ]; then
  echo "\"$apt_package_name\" is installed and will be uninstalled."
  sudo apt-get purge -y "$apt_package_name"
else
  echo "Skipping, no action needed, \"$apt_package_name\" is not installed."
fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -Remove daily cron entry for Popularity Contest (popcon)--
# ----------------------------------------------------------
echo '--- Remove daily cron entry for Popularity Contest (popcon)'
job_name='popularity-contest'
cronjob_path="/etc/cron.daily/$job_name"
if [[ -f "$cronjob_path" ]]; then
  if [[ -x "$cronjob_path" ]]; then
    sudo chmod -x "$cronjob_path"
    echo "Succesfully disabled cronjob \"$job_name\"."
  else
    echo "Skipping, cronjob \"$job_name\" is already disabled."
  fi
else
  echo "Skipping, \"$job_name\" cronjob is not found."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------------Remove `reportbug` package----------------
# ----------------------------------------------------------
echo '--- Remove `reportbug` package'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  apt_package_name='reportbug'
if status="$(dpkg-query -W --showformat='${db:Status-Status}' "$apt_package_name" 2>&1)" \
    && [ "$status" = installed ]; then
  echo "\"$apt_package_name\" is installed and will be uninstalled."
  sudo apt-get purge -y "$apt_package_name"
else
  echo "Skipping, no action needed, \"$apt_package_name\" is not installed."
fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------Remove Python modules for `reportbug`-----------
# ----------------------------------------------------------
echo '--- Remove Python modules for `reportbug`'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  apt_package_name='python3-reportbug'
if status="$(dpkg-query -W --showformat='${db:Status-Status}' "$apt_package_name" 2>&1)" \
    && [ "$status" = installed ]; then
  echo "\"$apt_package_name\" is installed and will be uninstalled."
  sudo apt-get purge -y "$apt_package_name"
else
  echo "Skipping, no action needed, \"$apt_package_name\" is not installed."
fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----Remove UI for reportbug (`reportbug-gtk` package)-----
# ----------------------------------------------------------
echo '--- Remove UI for reportbug (`reportbug-gtk` package)'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  apt_package_name='reportbug-gtk'
if status="$(dpkg-query -W --showformat='${db:Status-Status}' "$apt_package_name" 2>&1)" \
    && [ "$status" = installed ]; then
  echo "\"$apt_package_name\" is installed and will be uninstalled."
  sudo apt-get purge -y "$apt_package_name"
else
  echo "Skipping, no action needed, \"$apt_package_name\" is not installed."
fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Kill Zeitgeist daemon process---------------
# ----------------------------------------------------------
echo '--- Kill Zeitgeist daemon process'
if ! command -v 'zeitgeist-daemon' &> /dev/null; then
  echo 'Skipping because "zeitgeist-daemon" is not found.'
else
  zeitgeist-daemon --quit
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Remove Zeitgeist startup entry--------------
# ----------------------------------------------------------
echo '--- Remove Zeitgeist startup entry'
file='/etc/xdg/autostart/zeitgeist-datahub.desktop'
backup_file="${file}.old"
if [ -f "$file" ]; then
  echo "File exists: $file."
  sudo mv "$file" "$backup_file"
  echo "Moved to: $backup_file."
else
  echo "Skipping, no changes needed."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Disable access to Zeitgeist database-----------
# ----------------------------------------------------------
echo '--- Disable access to Zeitgeist database'
file="$HOME/.local/share/zeitgeist/activity.sqlite"
if [ -f "$file" ]; then
  chmod -rw "$file"
  echo "Successfully disabled read/write access to $file."
else
  echo "Skipping, no action needed, file does not exist at $file."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -Remove Zeitgeist package (can break integrated software)-
# ----------------------------------------------------------
echo '--- Remove Zeitgeist package (can break integrated software)'
if ! command -v 'apt-get' &> /dev/null; then
  echo 'Skipping because "apt-get" is not found.'
else
  apt_package_name='zeitgeist-core'
if status="$(dpkg-query -W --showformat='${db:Status-Status}' "$apt_package_name" 2>&1)" \
    && [ "$status" = installed ]; then
  echo "\"$apt_package_name\" is installed and will be uninstalled."
  sudo apt-get purge -y "$apt_package_name"
else
  echo "Skipping, no action needed, \"$apt_package_name\" is not installed."
fi
fi
if ! command -v 'pacman' &> /dev/null; then
  echo 'Skipping because "pacman" is not found.'
else
  pkg_package_name='zeitgeist'
if pacman -Qs "$pkg_package_name" > /dev/null ; then
  echo "\"$pkg_package_name\" is installed and will be uninstalled."
  sudo pacman -Rcns "$pkg_package_name" --noconfirm
else
  echo "The package $pkg_package_name is not installed"
fi
fi
if ! command -v 'dnf' &> /dev/null; then
  echo 'Skipping because "dnf" is not found.'
else
  rpm_package_name='zeitgeist'
sudo dnf autoremove -y --skip-broken "$rpm_package_name"
fi
# ----------------------------------------------------------


# Disable connectivity checks (breaks Captive Portal detection)
echo '--- Disable connectivity checks (breaks Captive Portal detection)'
if ! command -v '/usr/sbin/NetworkManager' &> /dev/null; then
  echo 'Skipping because "/usr/sbin/NetworkManager" is not found.'
else
  file='/etc/NetworkManager/conf.d/20-disable-connectivity-privacy-sexy.conf'
content=$'# Created by privacy.sexy\n[connectivity]\nenabled=false'
directory="${file%/*}"
mkdir -p "$directory"
if [ -f "$file" ]; then
  echo "Skipping, connectivity checks are already disabled through $file."
else
  echo -n "$content" | sudo tee "$file" > /dev/null
  echo 'Successfully disabled connectivity checks.'
fi
if command -v 'nmcli' &> /dev/null; then
  sudo nmcli general reload
  echo 'Successfully reloaded configuration.'
else
  echo 'It will take effect after reboot.'
fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --Disable automatic Visual Studio Code extension updates--
# ----------------------------------------------------------
echo '--- Disable automatic Visual Studio Code extension updates'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'extensions.autoUpdate'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable Visual Studio Code automatic extension update checks
echo '--- Disable Visual Studio Code automatic extension update checks'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'extensions.autoCheckUpdates'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable automatic fetching of Microsoft recommendations in Visual Studio Code
echo '--- Disable automatic fetching of Microsoft recommendations in Visual Studio Code'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'extensions.showRecommendationsOnlyOnDemand'
target = json.loads('true')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# Disable synchronization of Visual Studio Code keybindings-
# ----------------------------------------------------------
echo '--- Disable synchronization of Visual Studio Code keybindings'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'settingsSync.keybindingsPerPlatform'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -Disable synchronization of Visual Studio Code extensions-
# ----------------------------------------------------------
echo '--- Disable synchronization of Visual Studio Code extensions'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'settingsSync.ignoredExtensions'
target = json.loads('["*"]')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --Disable synchronization of Visual Studio Code settings--
# ----------------------------------------------------------
echo '--- Disable synchronization of Visual Studio Code settings'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'settingsSync.ignoredSettings'
target = json.loads('["*"]')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Disable Visual Studio Code telemetry-----------
# ----------------------------------------------------------
echo '--- Disable Visual Studio Code telemetry'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'telemetry.telemetryLevel'
target = json.loads('"off"')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'telemetry.enableTelemetry'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'telemetry.enableCrashReporter'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable online experiments by Microsoft in Visual Studio Code
echo '--- Disable online experiments by Microsoft in Visual Studio Code'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.enableExperiments'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable Visual Studio Code automatic updates in favor of manual updates
echo '--- Disable Visual Studio Code automatic updates in favor of manual updates'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'update.mode'
target = json.loads('"none"')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'update.channel'
target = json.loads('"none"')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable fetching release notes from Microsoft servers after an update
echo '--- Disable fetching release notes from Microsoft servers after an update'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'update.showReleaseNotes'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable automatic fetching of remote repositories in Visual Studio Code
echo '--- Disable automatic fetching of remote repositories in Visual Studio Code'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'git.autofetch'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable fetching package information from NPM and Bower in Visual Studio Code
echo '--- Disable fetching package information from NPM and Bower in Visual Studio Code'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'npm.fetchOnlinePackageInfo'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable sending search queries to Microsoft in Visual Studio Code
echo '--- Disable sending search queries to Microsoft in Visual Studio Code'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.settings.enableNaturalLanguageSearch'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# Disable Visual Studio Code automatic type acquisition in TypeScript
echo '--- Disable Visual Studio Code automatic type acquisition in TypeScript'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'typescript.disableAutomaticTypeAcquisition'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------Disable Visual Studio Code Edit Sessions---------
# ----------------------------------------------------------
echo '--- Disable Visual Studio Code Edit Sessions'
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.experimental.editSessions.enabled'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.experimental.editSessions.autoStore'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.editSessions.autoResume'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
if ! command -v 'python3' &> /dev/null; then
  echo 'Skipping because "python3" is not found.'
else
  python3 <<EOF
from pathlib import Path
import os, json, sys
property_name = 'workbench.editSessions.continueOn'
target = json.loads('false')
home_dir = f'/home/{os.getenv("SUDO_USER", os.getenv("USER"))}'
settings_files = [
  # Global installation (also Snap that installs with "--classic" flag)
  f'{home_dir}/.config/Code/User/settings.json',
  # Flatpak installation
  f'{home_dir}/.var/app/com.visualstudio.code/config/Code/User/settings.json'
]
for settings_file in settings_files:
  file=Path(settings_file)
  if not file.is_file():
    print(f'Skipping, file does not exist at "{settings_file}".')
    continue
  print(f'Reading file at "{settings_file}".')
  file_content = file.read_text()
  if not file_content.strip():
    print('Settings file is empty. Treating it as default empty JSON object.')
    file_content = '{}'
  json_object = None
  try:
    json_object = json.loads(file_content)
  except json.JSONDecodeError:
    print(f'Error, invalid JSON format in the settings file: "{settings_file}".', file=sys.stderr)
    continue
  if property_name not in json_object:
    print(f'Settings "{property_name}" is not configured.')
  else:
    existing_value = json_object[property_name]
    if existing_value == target:
      print(f'Skipping, "{property_name}" is already configured as {json.dumps(target)}.')
      continue
    print(f'Setting "{property_name}" has unexpected value {json.dumps(existing_value)} that will be changed.')
  json_object[property_name] = target
  new_content = json.dumps(json_object, indent=2)
  file.write_text(new_content)
  print(f'Successfully configured "{property_name}" to {json.dumps(target)}.')
EOF
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --Disable Python history for future interactive commands--
# ----------------------------------------------------------
echo '--- Disable Python history for future interactive commands'
history_file="$HOME/.python_history"
if [ ! -f "$history_file" ]; then
  touch "$history_file"
  echo "Created $history_file."
fi
sudo chattr +i "$(realpath $history_file)" # realpath in case of symlink
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------------Disable .NET telemetry------------------
# ----------------------------------------------------------
echo '--- Disable .NET telemetry'
variable='DOTNET_CLI_TELEMETRY_OPTOUT'
value='1'
declaration_file='/etc/environment'
if ! [ -f "$declaration_file" ]; then
  echo "\"$declaration_file\" does not exist."
  sudo touch "$declaration_file"
  echo "Created $declaration_file."
fi
assignment_start="$variable="
assignment="$variable=$value"
if ! grep --quiet "^$assignment_start" "${declaration_file}"; then
  echo "Variable \"$variable\" was not configured before."
  echo -n $'\n'"$assignment" | sudo tee -a "$declaration_file" > /dev/null
  echo "Successfully configured ($assignment)."
else
  if grep --quiet "^$assignment$" "${declaration_file}"; then
    echo "Skipping. Variable \"$variable\" is already set to value \"$value\"."
  else
    if ! sudo sed --in-place "/^$assignment_start/d" "$declaration_file"; then
      >&2 echo "Failed to delete assignment starting with \"$assignment_start\"."
    else
      echo "Successfully deleted unexpected assignment of \"$variable\"."
      if ! echo -n $'\n'"$assignment" | sudo tee -a "$declaration_file" > /dev/null; then
        >&2 echo "Failed to add assignment \"$assignment\"."
      else
        echo "Successfully reconfigured ($assignment)."
      fi
    fi
  fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------Disable PowerShell Core telemetry-------------
# ----------------------------------------------------------
echo '--- Disable PowerShell Core telemetry'
variable='POWERSHELL_TELEMETRY_OPTOUT'
value='1'
declaration_file='/etc/environment'
if ! [ -f "$declaration_file" ]; then
  echo "\"$declaration_file\" does not exist."
  sudo touch "$declaration_file"
  echo "Created $declaration_file."
fi
assignment_start="$variable="
assignment="$variable=$value"
if ! grep --quiet "^$assignment_start" "${declaration_file}"; then
  echo "Variable \"$variable\" was not configured before."
  echo -n $'\n'"$assignment" | sudo tee -a "$declaration_file" > /dev/null
  echo "Successfully configured ($assignment)."
else
  if grep --quiet "^$assignment$" "${declaration_file}"; then
    echo "Skipping. Variable \"$variable\" is already set to value \"$value\"."
  else
    if ! sudo sed --in-place "/^$assignment_start/d" "$declaration_file"; then
      >&2 echo "Failed to delete assignment starting with \"$assignment_start\"."
    else
      echo "Successfully deleted unexpected assignment of \"$variable\"."
      if ! echo -n $'\n'"$assignment" | sudo tee -a "$declaration_file" > /dev/null; then
        >&2 echo "Failed to add assignment \"$assignment\"."
      else
        echo "Successfully reconfigured ($assignment)."
      fi
    fi
  fi
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------Enable dynamic First-Party Isolation (dFPI)--------
# ----------------------------------------------------------
echo '--- Enable dynamic First-Party Isolation (dFPI)'
pref_name='network.cookie.cookieBehavior'
pref_value='5'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Enable Firefox network partitioning------------
# ----------------------------------------------------------
echo '--- Enable Firefox network partitioning'
pref_name='privacy.partition.network_state'
pref_value='true'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---Disable outdated Firefox First-Party Isolation (FPI)---
# ----------------------------------------------------------
echo '--- Disable outdated Firefox First-Party Isolation (FPI)'
pref_name='privacy.firstparty.isolate'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------Enable Firefox tracking protection------------
# ----------------------------------------------------------
echo '--- Enable Firefox tracking protection'
pref_name='privacy.trackingprotection.enabled'
pref_value='true'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# Enable Firefox anti-fingerprinting (may break some websites)
echo '--- Enable Firefox anti-fingerprinting (may break some websites)'
pref_name='privacy.resistFingerprinting'
pref_value='true'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# Disable WebRTC exposure of your private IP address in Firefox
echo '--- Disable WebRTC exposure of your private IP address in Firefox'
pref_name='media.peerconnection.ice.default_address_only'
pref_value='true'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------Minimize Firefox telemetry logging verbosity-------
# ----------------------------------------------------------
echo '--- Minimize Firefox telemetry logging verbosity'
pref_name='toolkit.telemetry.log.level'
pref_value='"Fatal"'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Disable Firefox telemetry log output-----------
# ----------------------------------------------------------
echo '--- Disable Firefox telemetry log output'
pref_name='toolkit.telemetry.log.dump'
pref_value='"Fatal"'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------Disable pings to Firefox telemetry server---------
# ----------------------------------------------------------
echo '--- Disable pings to Firefox telemetry server'
pref_name='toolkit.telemetry.server'
pref_value='""'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# --------------Disable Firefox shutdown ping---------------
# ----------------------------------------------------------
echo '--- Disable Firefox shutdown ping'
pref_name='toolkit.telemetry.shutdownPingSender.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
pref_name='toolkit.telemetry.shutdownPingSender.enabledFirstSession'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
pref_name='toolkit.telemetry.firstShutdownPing.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Disable Firefox new profile ping-------------
# ----------------------------------------------------------
echo '--- Disable Firefox new profile ping'
pref_name='toolkit.telemetry.newProfilePing.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------------Disable Firefox update ping----------------
# ----------------------------------------------------------
echo '--- Disable Firefox update ping'
pref_name='toolkit.telemetry.updatePing.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------------Disable Firefox prio ping-----------------
# ----------------------------------------------------------
echo '--- Disable Firefox prio ping'
pref_name='toolkit.telemetry.prioping.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# Disable collection of technical and interaction data in Firefox
echo '--- Disable collection of technical and interaction data in Firefox'
pref_name='datareporting.healthreport.uploadEnabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----Disable detailed telemetry collection in Firefox-----
# ----------------------------------------------------------
echo '--- Disable detailed telemetry collection in Firefox'
pref_name='toolkit.telemetry.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ----------Disable archiving of Firefox telemetry----------
# ----------------------------------------------------------
echo '--- Disable archiving of Firefox telemetry'
pref_name='toolkit.telemetry.archive.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------Disable Firefox unified telemetry-------------
# ----------------------------------------------------------
echo '--- Disable Firefox unified telemetry'
pref_name='toolkit.telemetry.unified'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear Firefox telemetry user ID--------------
# ----------------------------------------------------------
echo '--- Clear Firefox telemetry user ID'
pref_name='toolkit.telemetry.cachedClientID'
pref_value='""'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ---------Disable Firefox Pioneer study monitoring---------
# ----------------------------------------------------------
echo '--- Disable Firefox Pioneer study monitoring'
pref_name='toolkit.telemetry.pioneer-new-studies-available'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------Clear Firefox pioneer program ID-------------
# ----------------------------------------------------------
echo '--- Clear Firefox pioneer program ID'
pref_name='toolkit.telemetry.pioneerId'
pref_value='""'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----Disable blocking of unstable plugins in Firefox------
# ----------------------------------------------------------
echo '--- Disable blocking of unstable plugins in Firefox'
pref_name='browser.safebrowsing.blockedURIs.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# Disable Firefox application reputation checks for downloads
echo '--- Disable Firefox application reputation checks for downloads'
pref_name='browser.safebrowsing.downloads.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# ------------Disable Firefox malware protection------------
# ----------------------------------------------------------
echo '--- Disable Firefox malware protection'
pref_name='browser.safebrowsing.malware.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -----------Disable Firefox phishing protection------------
# ----------------------------------------------------------
echo '--- Disable Firefox phishing protection'
pref_name='browser.safebrowsing.phishing.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


# ----------------------------------------------------------
# -Disable connection tests (breaks automatic Wi-Fi login)--
# ----------------------------------------------------------
echo '--- Disable connection tests (breaks automatic Wi-Fi login)'
pref_name='network.captive-portal-service.enabled'
pref_value='false'
echo "Setting preference \"$pref_name\" to \"$pref_value\"."
declare -a profile_paths=(
  ~/.mozilla/firefox/*/
  ~/.var/app/org.mozilla.firefox/.mozilla/firefox/*/
  ~/snap/firefox/common/.mozilla/firefox/*/
)
declare -i total_profiles_found=0
for profile_dir in "${profile_paths[@]}"; do
  if [ ! -d "$profile_dir" ]; then
    continue
  fi
  if [[ ! "$(basename "$profile_dir")" =~ ^[a-z0-9]{8}\..+ ]]; then
    continue # Not a profile folder
  fi
  ((total_profiles_found++))
  user_js_file="${profile_dir}user.js"
  echo "$user_js_file:"
  if [ ! -f "$user_js_file" ]; then
    touch "$user_js_file"
    echo $'\t''Created new user.js file'
  fi
  pref_start="user_pref(\"$pref_name\","
  pref_line="user_pref(\"$pref_name\", $pref_value);"
  if ! grep --quiet "^$pref_start" "${user_js_file}"; then
    echo -n $'\n'"$pref_line" >> "$user_js_file"
    echo $'\t'"Successfully added a new preference in $user_js_file."
  elif grep --quiet "^$pref_line$" "$user_js_file"; then
    echo $'\t'"Skipping, preference is already set as expected in $user_js_file."
  else
    sed --in-place "/^$pref_start/c\\$pref_line" "$user_js_file"
    echo $'\t'"Successfully replaced the existing incorrect preference in $user_js_file."
  fi
done
if [ "$total_profiles_found" -eq 0 ]; then
  echo 'No profile folders are found, no changes are made.'
else
  echo "Successfully verified preferences in $total_profiles_found profiles."
fi
# ----------------------------------------------------------


echo 'Your privacy and security is now hardened 🎉💪'
echo 'Press any key to exit.'
read -n 1 -s
