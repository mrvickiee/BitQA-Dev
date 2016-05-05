CREATE TABLE `tblContent` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `content` text,
  `upvotes` int(11) DEFAULT NULL,
  `downvotes` int(11) DEFAULT NULL,
  `utimestamp` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
