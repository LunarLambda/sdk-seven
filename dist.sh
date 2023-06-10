#!/bin/sh

DIST=$PWD/dist

make_dist() {
    VERSION=$(grep "${PROJECT}_version" meson.build | cut -d"'" -f2)
    cd ${DIR:-$PROJECT}
    git archive -o $DIST/$PROJECT-$VERSION.zip \
        --prefix=$PROJECT-$VERSION/ --add-file=../LICENSE_MPL-2.0.txt --add-file=../LICENSE_CC0-1.0.txt HEAD .
    cd $DIST
    sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
}

[ ! -d "$DIST" ] && mkdir "$DIST" || rm "$DIST"/*

for p in libseven minrt libutil; do
    (PROJECT="$p" make_dist)
done
