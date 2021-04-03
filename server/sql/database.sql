CREATE DATABASE IF NOT EXISTS litt CHARACTER SET utf8 COLLATE utf8_general_ci;

CREATE TABLE diffs (  client_id              int not null,
                      device_id              varchar(255) not null,  
                      created                timestamp not null,
                      content                blob not null );

create table clients ( client_id             int not null,
                       username              varchar(255) not null,
                       password              varchar(255) not null);
                       
create table devices ( client_id             int not null,
                       device_id             int not null,
                       device_name           varchar(255) not null,
                       device_platform       int not null);
                       

                       
