#!/bin/bash
echo "dropping existing database"
mysql -e "drop database micro; create database micro;"
echo "importing the plain database"
mysql micro < micro_plain.sql
echo "done"
