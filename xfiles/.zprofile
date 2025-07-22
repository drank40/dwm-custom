#exec startx
#openrgb -p archultimate.orp
echo "Would you like to startx?"
echo "[Y]/N  "
read choice
if [ "$choice" = "y" ] || [ "$choice" = "Y" ] || [ "$choice" = "" ]; then
    exec startx
fi
