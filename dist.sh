#!/bin/sh

DIST=$PWD/dist

(
PROJECT=libseven
VERSION=0.7.1
cd $PROJECT
git archive -o $DIST/$PROJECT-$VERSION.zip --prefix=$PROJECT-$VERSION/ HEAD .
cd $DIST
sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
)

(
PROJECT=minrt
VERSION=0.2.0
cd $PROJECT
git archive -o $DIST/dist/$PROJECT-$VERSION.zip --prefix=$PROJECT-$VERSION/ HEAD .
cd $DIST
sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
)
