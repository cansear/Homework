use minnowdb;

CREATE TABLE `user_info` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(45) NOT NULL,
  `password` varchar(30) DEFAULT NULL,
  `role` int(11) NOT NULL,
  `status` int(11) NOT NULL COMMENT 'enabled or disabled',
  `address` varchar(200) DEFAULT NULL,
  `real_name` varchar(45) DEFAULT NULL,
  `register_time` datetime DEFAULT NULL,
  `register_ip` varchar(45) DEFAULT NULL,
  `last_login_time` datetime DEFAULT NULL,
  `last_login_ip` varchar(45) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `contact_phone` varchar(45) DEFAULT NULL,
  `company` varchar(45) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `gender` varchar(10) DEFAULT NULL,
  `birthdate` datetime DEFAULT NULL,
  `avatar` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
);
CREATE TABLE `project` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `description` varchar(45) DEFAULT NULL,
  `target_raise` float DEFAULT NULL,
  `property_type` int(11) DEFAULT NULL,
  `investment_type` int(11) DEFAULT NULL,
  `minimum_investment` float DEFAULT NULL,
  `total_funded` float DEFAULT NULL,
  `due_date` datetime DEFAULT NULL,
  `project_owner` varchar(45) DEFAULT NULL,
  `status` int(11) DEFAULT NULL COMMENT 'In progress / funded',
  `percentage` float DEFAULT NULL,
  `project_location` varchar(45) DEFAULT NULL,
  `start_date` datetime DEFAULT NULL COMMENT 'date time when this project start to raise',
  `post_date` datetime DEFAULT NULL COMMENT 'date time when this project was posted',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
);

CREATE TABLE `user_project` (
  `user_id` int(11) NOT NULL,
  `project_id` int(11) NOT NULL,
  PRIMARY KEY (`user_id`,`project_id`),
  KEY `FK_USER_RELATE_PROJECT` (`user_id`),
  KEY `FK_PROJECT_RELATE_USER` (`project_id`),
  CONSTRAINT `FK_USER_RELATE_PROJECT` FOREIGN KEY (`user_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_PROJECT_RELATE_USER` FOREIGN KEY (`project_id`) REFERENCES `project` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
);
CREATE TABLE `account` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `balance` float NOT NULL COMMENT 'current account value',
  `user_id` int(11) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `account_name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id_UNIQUE` (`user_id`),
  KEY `FK_USER_ACCOUNT` (`user_id`),
  CONSTRAINT `FK_USER_ACCOUNT` FOREIGN KEY (`user_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
);

CREATE TABLE `comments` (
  `id` int(11) NOT NULL,
  `title` varchar(45) DEFAULT NULL,
  `sender_id` int(11) DEFAULT NULL,
  `sender_name` varchar(45) DEFAULT NULL,
  `reply_date` datetime DEFAULT NULL,
  `content` varchar(500) DEFAULT NULL,
  `project_id` int(11) DEFAULT NULL,
  `parent_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_USER_REPLY` (`sender_id`),
  KEY `FK_PROJECT_REPLY` (`project_id`),
  CONSTRAINT `FK_USER_REPLY` FOREIGN KEY (`sender_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_PROJECT_REPLY` FOREIGN KEY (`project_id`) REFERENCES `project` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
);

CREATE TABLE `message` (
  `id` int(11) NOT NULL,
  `receiver_id` int(11) NOT NULL,
  `sender_id` int(11) DEFAULT NULL,
  `subject` varchar(45) DEFAULT NULL,
  `message` varchar(45) DEFAULT NULL,
  `send_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_RECEIVER_MESSAGE` (`receiver_id`),
  KEY `FK_SENDER_MESSAGE` (`sender_id`),
  CONSTRAINT `FK_RECEIVER_MESSAGE` FOREIGN KEY (`receiver_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_SENDER_MESSAGE` FOREIGN KEY (`sender_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
);

CREATE TABLE `user_registration` (
  `user_id` int(11) NOT NULL,
  `registration` varchar(45) NOT NULL COMMENT 'nickname/cellphone number/ email address/ wechat id/ ...',
  `registration_type` int(11) NOT NULL COMMENT 'wechat/ tweeter/ g+/facebook/...',
  PRIMARY KEY (`user_id`,`registration_type`),
  UNIQUE KEY `registration_UNIQUE` (`registration`),
  KEY `FK_USER` (`user_id`),
  CONSTRAINT `FK_USER` FOREIGN KEY (`user_id`) REFERENCES `user_info` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
);





