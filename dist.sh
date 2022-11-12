#!/bin/sh

(
PROJECT=libseven
VERSION=0.7.1
cd subprojects/$PROJECT
git archive -o ../../dist/$PROJECT-$VERSION.zip --prefix=$PROJECT-$VERSION/ HEAD .
cd ../../dist
sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
)

(
PROJECT=minrt
VERSION=0.2.0
cd subprojects/$PROJECT
git archive -o ../../dist/$PROJECT-$VERSION.zip --prefix=$PROJECT-$VERSION/ HEAD .
cd ../../dist
sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
)
