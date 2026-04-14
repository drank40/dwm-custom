#!/bin/sh
sudo nix-update dwm-custom --file /etc/nixos/pkgs/dwm-custom.nix --version branch=main
sudo nixos-rebuild switch --impure --flake /etc/nixos#nsa-router
