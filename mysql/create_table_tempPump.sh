#! /bin/bash
mysql -e "
use LilCabinPump;
delimiter //
CREATE TABLE pumpTemp (
  id int(11) NOT NULL AUTO_INCREMENT,
  message text NOT NULL,
  date_received timestamp default current_timestamp,
  PRIMARY KEY (id)
)
 //
GRANT ALL PRIVILEGES ON LilCabinPump.pumpTemp to 'pi'@'localhost'
 //
"
