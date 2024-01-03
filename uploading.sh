#!/bin/sh


echo "# HTTPS-server" >> README.md
git init
git add README.md
echo "Committing"
git commit -m "first commit"
echo "Branching"
git branch -M main
echo "Adding to remote origin"
git remote add origin git@github.com:Lekhanya/HTTPS-server.git
git push -u origin main
