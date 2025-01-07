mysql -u pi -plilcabin LilCabinPump -e "select date_received,right(message,25) as InsideTemp, local_temp from pumpTemp order by date_received desc limit 15"
