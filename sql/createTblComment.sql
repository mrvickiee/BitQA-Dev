
CREATE TABLE `tblComment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `contentId` int(11) DEFAULT NULL,
  `parentContentId` int(11) DEFAULT NULL,
  `aowner` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SELECT * FROM BitQA.tblContent;