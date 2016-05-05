CREATE TABLE `tblUser` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(45) DEFAULT NULL,
  `passhash` varchar(45) DEFAULT NULL,
  `displayname` varchar(45) DEFAULT NULL,
  `creationdate` datetime DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `location` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
