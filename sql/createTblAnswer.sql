CREATE TABLE `tblAnswer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `contentId` int(11) DEFAULT NULL,
  `questionId` int(11) DEFAULT NULL,
  `aowner` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SELECT * FROM BitQA.tblContent;