make clean
A=`date +"%s"`
cd .. && tar -cvzf pocket_starfighter-$A.tar.gz pocket_starfighter
echo "Backup $A done."
