insert into together.t_file (id, md5, suffix, uploader_id) values (1, '00729817beb2031f93d715c4c967aa8e', '.png', 1);
insert into together.t_file (id, md5, suffix, uploader_id) values (2, 'adfd71501248d0a6e29f357f4c5ba96d', '.caf', 1);
insert into together.t_user (id, username, password, nickname, birthday, signature_text, signature_record_id, pic_id, praise_num, visit_num, sex) values 
(1, 'admin', 'a', 'G-Mart', 20000101010203, 'hello', 2, 1, 0, 0, 0),
(2, 'admin2', 'a', 'G-Mart2', 20000101010203, 'hello', 2, 1, 0, 0, 1);
INSERT INTO together.t_address (`id`, `addr_type`, `latitude`, `longitude`, `detail_addr`, `addr_remark`) VALUES
(1000, 2, 23.041559, 113.374646, '红棉路', '借单车处'),
(1001, 1, 23.041228, 113.375483, '红棉路', '711');
INSERT INTO together.t_room (`id`, `owner_id`, `title`, `type`, `gender_type`, `room_status`, `limit_person_num`, `preview_pic_id`, `addr_id`, `record_id`, `begin_time`, `create_time`) VALUES
(1000, 1, '踩单车', 2, 0, 0, 10, 1, 1000, 2, '2013-05-31 17:02:03', '2000-12-31 17:01:01'),
(1001, 1, '狼人', 1, 0, 0, 10, 1, 1001, 2, '2013-05-31 17:02:03', '2000-12-31 17:01:01');
INSERT INTO together.t_room_user_relation (room_id, user_id) values (1000, 1);