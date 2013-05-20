insert into together.t_file (id, md5, suffix, uploader_id) values 
(1, '00729817beb2031f93d715c4c967aa8e', '.png', 1)
,(2, 'adfd71501248d0a6e29f357f4c5ba96d', '.caf', 1);
insert into together.t_user 
(id, username, password, nickname, birthday, signature_text, signature_record_id, pic_id, praise_num, visit_num, sex) values 
(1, 'admin', '123456', 'G-Mart', 20000101010203, 'hello', 2, 1, 0, 0, 0)
,(2, 'admin2', '123456', 'G-Mart2', 20000101010203, 'hello', 2, 1, 0, 0, 1)
,(3, 'admin3', '123456', 'G-Mart3', 20000101010203, 'hello', 2, 1, 0, 0, 1)
,(4, 'followtest', '123456', 'followtest', 20000101010203, 'hello', 2, 1, 0, 0, 1)
,(5, 'sender', '123456', 'sender', 20000101010203, 'hello', 2, 1, 0, 0, 1)
,(6, 'recipient', '123456', 'recipient', 20000101010203, 'hello', 2, 1, 0, 0, 1);
INSERT INTO together.t_address 
(`id`, `addr_type`, `latitude`, `longitude`, `detail_addr`, `addr_remark`) VALUES
(1000, 2, 23.041559, 113.374646, '红棉路', '借单车处')
,(1001, 1, 23.041228, 113.375483, '红棉路', '711');
INSERT INTO together.t_room 
(`id`, `owner_id`, `title`, `type`, `gender_type`, `room_status`, `limit_person_num`, `preview_pic_id`, `addr_id`, `record_id`, `begin_time`, `create_time`) VALUES
(1000, 1, '踩单车', 2, 0, 0, 10, 1, 1000, 2, '2013-05-31 17:02:03', '2000-12-31 17:01:01')
,(1001, 2, '狼人', 1, 0, 0, 10, 1, 1001, 2, '2013-05-31 17:02:03', '2000-12-31 17:01:01');
INSERT INTO together.t_room_user_relation 
(room_id, user_id) values 
(1001, 1)
,(1001, 3);
insert into together.t_follow 
(followed_id, follow_id) values 
(3, 1)
,(4, 1)
,(4, 2)
,(4, 3)
,(1, 4)
,(2, 4);
insert into together.t_msg 
(id, sender_id, recipient_id, room_id, type, content) values 
(1, 5, 6, 56, 2, '1')
,(2, 5, 6, 56, 2, '2')
,(3, 5, 6, 56, 2, '3')
,(4, 6, 6, 66, 2, '4')
,(5, 4, 6, 46, 2, '5')
,(6, 4, 6, 46, 2, '6')
,(7, 4, 6, 46, 2, '7');