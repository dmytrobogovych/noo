if [ -f ./$1 ];
then
	echo "File $1 exists."
	echo Copying build
	if cp -f ./$1 /var/www/satorilight.com/public_html/downloads
	then
		echo Updating links
		sed -i "s/Litt-osx.*\\.zip/$1/g" /var/www/satorilight.com/public_html/index.html
		rm -f /var/www/satorilight.com/public_html/downloads/litt-osx.zip
		ln -s /var/www/satorilight.com/public_html/downloads/$1 /var/www/satorilight.com/public_html/downloads/litt-osx.zip

		if [ -f changelog.txt ];
		then
			echo "changelog.txt exists, copying to website"
			rm -rf /var/www/satorilight.com/public_html/changelog.txt
			cp changelog.txt /var/www/satorilight.com/public_html/
		fi
	fi
else
   echo "File $1 does not exist."
fi
