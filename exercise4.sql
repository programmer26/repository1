drop database if exists Example;
create database Example;
use Example;

create table Group1(name varchar(100) not null, date_joined varchar(100) not null);

insert into Group1 values("Boris", "11-11-2020");

select * from Group1;
