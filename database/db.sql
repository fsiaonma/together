SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `together` ;
CREATE SCHEMA IF NOT EXISTS `together` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `together` ;

-- -----------------------------------------------------
-- Table `together`.`t_file`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_file` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_file` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `suffix` VARCHAR(45) NULL ,
  `md5` VARCHAR(45) NULL ,
  `uploader_id` INT NULL ,
  `upload_time` TIMESTAMP NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `together`.`t_user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_user` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_user` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(30) NULL ,
  `password` VARCHAR(20) NULL ,
  `nick_name` VARCHAR(30) NULL ,
  `birthday` TIMESTAMP NULL ,
  `signature_text` VARCHAR(255) NULL COMMENT '个性签名(文字)' ,
  `signature_record_id` INT NULL COMMENT '个性签名(语音文件ID)' ,
  `praise_num` INT NULL COMMENT '赞次数' ,
  `visit_num` INT NULL COMMENT '访问次数' ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_user_t_file1_idx` (`signature_record_id` ASC) ,
  CONSTRAINT `fk_t_user_t_file1`
    FOREIGN KEY (`signature_record_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `together`.`t_address`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_address` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_address` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `addr_type` INT NULL ,
  `longitude` FLOAT NULL COMMENT '经度' ,
  `latitude` FLOAT NULL COMMENT '纬度' ,
  `detail_addr` VARCHAR(255) NULL COMMENT '详细地址' ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `together`.`t_room`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_room` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_room` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `owner_id` INT NULL ,
  `tittle` VARCHAR(255) NULL ,
  `type` INT NULL ,
  `gender_type` INT NULL COMMENT '0,1,2\n表示参加活动的性别限制类型' ,
  `limit_person_num` INT NULL COMMENT '-1表示不限制' ,
  `preview_pic_id` INT NULL ,
  `addr_id` INT NULL COMMENT '地址表ID' ,
  `record_id` INT NULL COMMENT '录音文件id' ,
  `room_describe` VARCHAR(255) NULL COMMENT '房间描述' ,
  `begin_time` TIMESTAMP NULL ,
  `end_time` TIMESTAMP NULL ,
  `create_time` TIMESTAMP NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_room_t_address_idx` (`addr_id` ASC) ,
  INDEX `fk_t_room_t_file1_idx` (`record_id` ASC) ,
  INDEX `fk_t_room_t_file2_idx` (`preview_pic_id` ASC) ,
  INDEX `fk_t_room_t_user1_idx` (`owner_id` ASC) ,
  CONSTRAINT `fk_t_room_t_address`
    FOREIGN KEY (`addr_id` )
    REFERENCES `together`.`t_address` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_room_t_file1`
    FOREIGN KEY (`record_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_room_t_file2`
    FOREIGN KEY (`preview_pic_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_room_t_user1`
    FOREIGN KEY (`owner_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `together`.`t_room_user_relation`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_room_user_relation` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_room_user_relation` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `room_id` INT NULL ,
  `user_id` INT NULL COMMENT '房间用户关系表' ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_room_user_relation_t_room1_idx` (`room_id` ASC) ,
  INDEX `fk_t_room_user_relation_t_user1_idx` (`user_id` ASC) ,
  CONSTRAINT `fk_t_room_user_relation_t_room1`
    FOREIGN KEY (`room_id` )
    REFERENCES `together`.`t_room` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_room_user_relation_t_user1`
    FOREIGN KEY (`user_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `together`.`t_follow`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_follow` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_follow` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `followed_id` INT NULL COMMENT '被关注人id' ,
  `follow_id` INT NULL COMMENT '关注人id' ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_follow_t_user1_idx` (`followed_id` ASC) ,
  INDEX `fk_t_follow_t_user2_idx` (`follow_id` ASC) ,
  CONSTRAINT `fk_t_follow_t_user1`
    FOREIGN KEY (`followed_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_follow_t_user2`
    FOREIGN KEY (`follow_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `together` ;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
