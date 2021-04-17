#!/bin/bash
echo "dropping existing database"
mysql -e "drop database mibench; create database mibench;"
echo "importing the plain database (this takes some time)"
mysql mibench < mibench_plain.sql
echo "done"
