#!/bin/sh
# sed neutralizes version so nix-update's same-string guard don't bail
set -e
sudo sed -i 's|version = "[^"]*";|version = "0.0.0";|' /etc/nixos/pkgs/dwm-custom.nix
sudo sh -c 'cd /etc/nixos && nix-update dwm-custom --file /etc/nixos/pkgs/dwm-custom.nix --version branch=main'
sudo nixos-rebuild switch --impure --flake /etc/nixos#nsa-router
