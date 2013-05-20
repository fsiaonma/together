SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `together` ;
CREATE SCHEMA IF NOT EXISTS `together` DEFAULT CHARACTER SET utf8 ;
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
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


-- -----------------------------------------------------
-- Table `together`.`t_user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_user` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_user` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(30) NULL ,
  `password` VARCHAR(20) NULL ,
  `nickname` VARCHAR(30) NULL ,
  `birthday` DATE NULL ,
  `signature_text` VARCHAR(255) NULL COMMENT '个性签名(文字)' ,
  `signature_record_id` INT NULL COMMENT '个性签名(语音文件ID)' ,
  `pic_id` INT NULL ,
  `praise_num` INT NULL DEFAULT 0 COMMENT '赞次数' ,
  `visit_num` INT NULL COMMENT '访问次数' ,
  `sex` INT NULL COMMENT '0为男\n1为女' ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_user_t_file1_idx` (`signature_record_id` ASC) ,
  INDEX `fk_t_user_t_file2_idx` (`pic_id` ASC) ,
  CONSTRAINT `fk_t_user_t_file1`
    FOREIGN KEY (`signature_record_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_user_t_file2`
    FOREIGN KEY (`pic_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


-- -----------------------------------------------------
-- Table `together`.`t_address`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_address` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_address` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `addr_type` INT NULL ,
  `longitude` DOUBLE NULL COMMENT '经度' ,
  `latitude` DOUBLE NULL COMMENT '纬度' ,
  `detail_addr` VARCHAR(255) NULL COMMENT '详细地址' ,
  `addr_remark` VARCHAR(255) NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `lat_lng` (`longitude` ASC, `latitude` ASC) )
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


-- -----------------------------------------------------
-- Table `together`.`t_room`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_room` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_room` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `owner_id` INT NULL ,
  `title` VARCHAR(255) NULL ,
  `type` INT NULL ,
  `gender_type` INT NULL COMMENT '0,1,2\n表示参加活动的性别限制类型' ,
  `room_status` INT NULL COMMENT '房间状态' ,
  `limit_person_num` INT NULL COMMENT '-1表示不限制' ,
  `preview_pic_id` INT NULL ,
  `addr_id` INT NULL COMMENT '地址表ID' ,
  `record_id` INT NULL COMMENT '录音文件id' ,
  `begin_time` TIMESTAMP NULL ,
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
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


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
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


-- -----------------------------------------------------
-- Table `together`.`t_follow`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_follow` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_follow` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `followed_id` INT NULL COMMENT '被关注人id' ,
  `follow_id` INT NULL COMMENT '关注人id' ,
  `status` INT NULL ,
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
ENGINE = InnoDB
AUTO_INCREMENT = 1000;


-- -----------------------------------------------------
-- Table `together`.`t_msg`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `together`.`t_msg` ;

CREATE  TABLE IF NOT EXISTS `together`.`t_msg` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `sender_id` INT NULL ,
  `recipient_id` INT NULL ,
  `type` INT NULL ,
  `content` VARCHAR(255) NULL ,
  `title` VARCHAR(255) NULL ,
  `file_id` INT NULL ,
  `time` TIMESTAMP NULL ,
  `room_id` VARCHAR(45) NULL ,
  `status` TINYINT(1) NULL DEFAULT 0 ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_t_msg_t_user1_idx` (`sender_id` ASC) ,
  INDEX `fk_t_msg_t_file1_idx` (`file_id` ASC) ,
  INDEX `fk_t_msg_t_user2_idx` (`recipient_id` ASC) ,
  CONSTRAINT `fk_t_msg_t_user1`
    FOREIGN KEY (`sender_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_msg_t_file1`
    FOREIGN KEY (`file_id` )
    REFERENCES `together`.`t_file` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_t_msg_t_user2`
    FOREIGN KEY (`recipient_id` )
    REFERENCES `together`.`t_user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 1000;

USE `together` ;

-- -----------------------------------------------------
-- procedure pr_join_room
-- -----------------------------------------------------

USE `together`;
DROP procedure IF EXISTS `together`.`pr_join_room`;

DELIMITER $$
USE `together`$$
# call pr_join_room(1000,2,@ret);
create procedure pr_join_room 
(  
in i_room_id int   
, in i_user_id int
, out ret int
, out now_room_peo_list varchar(255)
)

BEGIN
#用于判断房间是否存在
declare v_room_num int;
#用于判断用户是否存在
declare v_user_num int;
#用于判断用户是否已经加入该房间
declare v_isjoin_num int;
#房间限制的人数
declare v_limit_person_num int;
#房间已加入的人数
declare v_join_person_num int;

#房间已加入的人
declare v_user_id int;
declare Done int default 0;

# 标记事务是否出错
declare t_error int default 0;
-- 声明游标
DECLARE rs CURSOR FOR 
SELECT user_id FROM t_room_user_relation where room_id = i_room_id
UNION
select owner_id from t_room where id = i_room_id;

# 如果出现sql异常，则将t_error设置为1后继续执行后面的操作
declare continue handler for sqlexception set t_error=1;


# set DB_PR_ERR
set ret = 5199;
set now_room_peo_list = '';

#判断用房间是否存在
select count(1) into v_user_num from t_user where id = i_user_id;
select count(1) into v_room_num from t_room where id = i_room_id and room_status = 0;
if v_user_num = 0 or v_room_num = 0 then
	#set DB_PR_PARAM_ERR
	set ret = v_user_num + v_room_num;
else
	# 判断当前用户是否已加入房间
	select count(1) into v_isjoin_num from t_room_user_relation rel 
		where rel.room_id = i_room_id and rel.user_id = i_user_id;
	if v_isjoin_num > 0 then
		set ret = 5102;
	else
		# 查出房间限制人数和当前已参加的人数
		SELECT r.limit_person_num, 
		(select count(1) from together.t_room_user_relation rel where rel.room_id = r.id) into 
			v_limit_person_num, v_join_person_num FROM together.t_room r limit 1;
		# 当参加人数不限 或 参加人数小于上限
		if v_limit_person_num = -1 or (v_join_person_num + 1) < v_limit_person_num then
			# 关闭事务的自动提交
			set autocommit = 0;
			# 插入到房间人员关系表
			insert into t_room_user_relation (room_id, user_id)
				values (i_room_id, i_user_id);
			if t_error=1 then  
				set ret = 5199;
				rollback; # 事务回滚  
			else  
				set ret = 5101;
				commit; # 事务提交
			end if;
		else
			# 房间人数已达到上限
			set ret = 5103;
		end if;
	end if;
end if;

begin
DECLARE CONTINUE HANDLER FOR NOT FOUND SET Done = 1;
OPEN rs;
	FETCH NEXT FROM rs INTO v_user_id;
	REPEAT
		IF NOT Done THEN
			set now_room_peo_list = concat(now_room_peo_list, '|', v_user_id);
		END IF;
	FETCH NEXT FROM rs INTO v_user_id;
	UNTIL Done END REPEAT;
CLOSE rs;
end;

#显示结果
-- select ret, now_room_peo_list;
end$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure pr_quit_room
-- -----------------------------------------------------

USE `together`;
DROP procedure IF EXISTS `together`.`pr_quit_room`;

DELIMITER $$
USE `together`$$
# call pr_quit_room(1000,2,@ret);
create procedure pr_quit_room 
(  
in i_room_id int   
, in i_user_id int
, out ret int  
, out now_room_peo_list varchar(255)
)
BEGIN
#用于判断房间是否存在
declare v_room_num int;
#用于判断用户是否存在
declare v_user_num int;
#用于判断用户是否已经加入该房间
declare v_isjoin_num int;
#用于判断用户是否为房主
declare v_isowner_num int;

#房间已加入的人
declare v_user_id int;
declare Done int default 0;

# 标记事务是否出错
declare t_error int default 0;
-- 声明游标
DECLARE rs CURSOR FOR 
SELECT user_id FROM t_room_user_relation where room_id = i_room_id
UNION
select owner_id from t_room where id = i_room_id;

# 如果出现sql异常，则将t_error设置为1后继续执行后面的操作
declare continue handler for sqlexception set t_error=1;


# set DB_PR_ERR
set ret = 5199;
set now_room_peo_list = '';


#判断用户,房间是否存在
select count(1) into v_user_num from t_user where id = i_user_id;
select count(1) into v_room_num from t_room where id = i_room_id and room_status = 0;
if v_user_num = 0 or v_room_num = 0 then
	#set DB_PR_PARAM_ERR
	set ret = 5100;
else
	#判断用户是否为房主
	select count(1) into v_isowner_num from t_room where id = i_room_id and owner_id = i_user_id;
	if v_isowner_num > 0 then
		set ret = 5106;
	else
		# 判断当前用户是否已加入房间
		select count(1) into v_isjoin_num from t_room_user_relation rel where rel.room_id = i_room_id and rel.user_id = i_user_id;
		if v_isjoin_num = 0 then
			set ret = 5105;
		else
			# 关闭事务的自动提交
			set autocommit = 0;
			# 删除房间人员关系表的记录
			delete from t_room_user_relation where room_id = i_room_id and user_id = i_user_id;
			if t_error=1 then  
				set ret = 5199;
				rollback; # 事务回滚  
			else  
				set ret = 5104;
				commit; # 事务提交
			end if;
		end if;
	end if;
end if;


begin
DECLARE CONTINUE HANDLER FOR NOT FOUND SET Done = 1;
OPEN rs;
	FETCH NEXT FROM rs INTO v_user_id;
	REPEAT
		IF NOT Done THEN
			set now_room_peo_list = concat(now_room_peo_list, '|', v_user_id);
		END IF;
	FETCH NEXT FROM rs INTO v_user_id;
	UNTIL Done END REPEAT;
CLOSE rs;
end;

#显示结果
-- select ret, now_room_peo_list;
end$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure pr_insert_msg
-- -----------------------------------------------------

USE `together`;
DROP procedure IF EXISTS `together`.`pr_insert_msg`;

DELIMITER $$
USE `together`$$
create procedure pr_insert_msg 
(  
in i_sender_id int   
, in i_recipient_id int
, in i_room_id int
, in i_msg_type int
, in i_content varchar(255)
, out ret int
, out send_user_list varchar(255)
)

BEGIN

DECLARE v_sender_exist int;
DECLARE v_recipient_exist int;
DECLARE v_room_exist int;
DECLARE v_user_id int;
DECLARE Done INT DEFAULT 0;
-- 声明游标
DECLARE rs CURSOR FOR SELECT user_id FROM t_room_user_relation where room_id = i_room_id;
# 如果出现sql异常，则将ret设为5199并退出
declare exit handler for sqlexception
begin
set ret = 5199;
rollback;
-- select ret;
end;


begin

DECLARE CONTINUE HANDLER FOR NOT FOUND SET Done = 1;

set send_user_list = '';

-- 判断发送人是否存在
select count(1) into v_sender_exist from t_user where id = i_sender_id;
if v_sender_exist = 0 then
	set ret = 5107; -- 发送人不存在
else
	if i_msg_type = 1 then -- 房间群聊
		-- 判断房间是否存在
		select count(1) into v_room_exist from t_room where id = i_room_id;
		if v_room_exist = 0 then
			set ret = 5108; -- 房间不存在
		else
			-- 房主
			select owner_id into v_user_id from t_room where id = i_room_id;
			-- if v_user_id <> i_sender_id then
				insert into t_msg (sender_id, recipient_id, type, content, room_id, time)
					values (i_sender_id, v_user_id, i_msg_type, i_content, i_room_id, now());
				set send_user_list = concat(send_user_list, '', v_user_id);
			-- end if;
			-- 已加入房间的人
			OPEN rs;
				FETCH NEXT FROM rs INTO v_user_id;
				REPEAT
					IF NOT Done THEN
						-- if v_user_id <> i_sender_id then
							insert into t_msg (sender_id, recipient_id, type, content, room_id, time)
								values (i_sender_id, v_user_id, i_msg_type, i_content, i_room_id, now());
							
							set send_user_list = concat(send_user_list, '|', v_user_id);
						-- end if;
					END IF;
				FETCH NEXT FROM rs INTO v_user_id;
				UNTIL Done END REPEAT;
			CLOSE rs;
			set ret = 5111; -- 插入成功
		end if;
	elseif i_msg_type = 2 then -- 私聊
		select count(1) into v_recipient_exist from t_user where id = i_recipient_id;
		if v_recipient_exist = 0 then
			set ret = 5109; -- 接收人不存在
		else
			insert into t_msg (sender_id, recipient_id, type, content, room_id, time, status)
				values (i_sender_id, i_recipient_id, i_msg_type, i_content, i_room_id, now(), false);
			set send_user_list = concat(send_user_list, '', i_recipient_id);

			insert into t_msg (sender_id, recipient_id, type, content, room_id, time, status)
				values (i_sender_id, i_sender_id, i_msg_type, i_content, i_room_id, now(), false);
			
			set ret = 5111; -- 插入成功
		end if;
	else -- 类型出错
		set ret = 5110; -- 类型错误
	end if;
	commit;
end if;

-- select ret, send_user_list;
end;

end$$

DELIMITER ;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
