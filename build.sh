#!/bin/bash

echo Running simple build script...

make || exit 1

echo Build completed.

echo Starting program...

./Spaceship
