CREATE TABLE `tblQuestion` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `questionTitle` text,
  `contentId` int(11) DEFAULT NULL,
  `acceptedAnswer` int(11) DEFAULT NULL,
  `viewcount` int(11) DEFAULT NULL,
  `qowner` int(11) DEFAULT NULL,
  `tags` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
