#!/usr/bin/env bash

set -ev

cd linux-network-program/tiny-chat

cd tiny-chat-02

protoc --cpp_out=. chat.message_unit.proto

cd ..

cd tiny-chat-03

protoc --cpp_out=. chat.message_unit.proto
protoc --cpp_out=. chat.heartbeat.proto

cd ..

cd tiny-chat-04

protoc --cpp_out=. chat.message_unit.proto
protoc --cpp_out=. chat.heartbeat.proto

cd ..

cd tiny-chat-05

protoc --cpp_out=. chat.message_unit.proto
protoc --cpp_out=. chat.heartbeat.proto

cd ..

cd tiny-chat-06

protoc --cpp_out=. chat.message_unit.proto
protoc --cpp_out=. chat.heartbeat.proto

cd ..

cd tiny-chat-07

protoc --cpp_out=. chat.message_unit.proto
protoc --cpp_out=. chat.heartbeat.proto

cd ..

