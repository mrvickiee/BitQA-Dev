CREATE TABLE `tblvotes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `contentId` int(11) NOT NULL,
  `userId` int(11) NOT NULL,
  `trans` enum('up','down','removeup','removedown') DEFAULT NULL,
  `processed` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
