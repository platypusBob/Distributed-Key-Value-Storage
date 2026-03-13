#!/bin/bash

timestamp=$(date +"%Y-%m-%d_%H-%M-%S")
mv log.aof ./aof_archive/log_${timestamp}.aof
