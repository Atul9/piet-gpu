// Code auto-generated by piet-gpu-derive

struct PathFillLineRef {
    uint offset;
};

struct PathStrokeLineRef {
    uint offset;
};

struct PathSegRef {
    uint offset;
};

struct PathFillLine {
    vec2 p0;
    vec2 p1;
    uint path_ix;
};

#define PathFillLine_size 20

PathFillLineRef PathFillLine_index(PathFillLineRef ref, uint index) {
    return PathFillLineRef(ref.offset + index * PathFillLine_size);
}

struct PathStrokeLine {
    vec2 p0;
    vec2 p1;
    uint path_ix;
    vec2 stroke;
};

#define PathStrokeLine_size 28

PathStrokeLineRef PathStrokeLine_index(PathStrokeLineRef ref, uint index) {
    return PathStrokeLineRef(ref.offset + index * PathStrokeLine_size);
}

#define PathSeg_Nop 0
#define PathSeg_FillLine 1
#define PathSeg_StrokeLine 2
#define PathSeg_size 32

PathSegRef PathSeg_index(PathSegRef ref, uint index) {
    return PathSegRef(ref.offset + index * PathSeg_size);
}

PathFillLine PathFillLine_read(PathFillLineRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = pathseg[ix + 0];
    uint raw1 = pathseg[ix + 1];
    uint raw2 = pathseg[ix + 2];
    uint raw3 = pathseg[ix + 3];
    uint raw4 = pathseg[ix + 4];
    PathFillLine s;
    s.p0 = vec2(uintBitsToFloat(raw0), uintBitsToFloat(raw1));
    s.p1 = vec2(uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.path_ix = raw4;
    return s;
}

void PathFillLine_write(PathFillLineRef ref, PathFillLine s) {
    uint ix = ref.offset >> 2;
    pathseg[ix + 0] = floatBitsToUint(s.p0.x);
    pathseg[ix + 1] = floatBitsToUint(s.p0.y);
    pathseg[ix + 2] = floatBitsToUint(s.p1.x);
    pathseg[ix + 3] = floatBitsToUint(s.p1.y);
    pathseg[ix + 4] = s.path_ix;
}

PathStrokeLine PathStrokeLine_read(PathStrokeLineRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = pathseg[ix + 0];
    uint raw1 = pathseg[ix + 1];
    uint raw2 = pathseg[ix + 2];
    uint raw3 = pathseg[ix + 3];
    uint raw4 = pathseg[ix + 4];
    uint raw5 = pathseg[ix + 5];
    uint raw6 = pathseg[ix + 6];
    PathStrokeLine s;
    s.p0 = vec2(uintBitsToFloat(raw0), uintBitsToFloat(raw1));
    s.p1 = vec2(uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.path_ix = raw4;
    s.stroke = vec2(uintBitsToFloat(raw5), uintBitsToFloat(raw6));
    return s;
}

void PathStrokeLine_write(PathStrokeLineRef ref, PathStrokeLine s) {
    uint ix = ref.offset >> 2;
    pathseg[ix + 0] = floatBitsToUint(s.p0.x);
    pathseg[ix + 1] = floatBitsToUint(s.p0.y);
    pathseg[ix + 2] = floatBitsToUint(s.p1.x);
    pathseg[ix + 3] = floatBitsToUint(s.p1.y);
    pathseg[ix + 4] = s.path_ix;
    pathseg[ix + 5] = floatBitsToUint(s.stroke.x);
    pathseg[ix + 6] = floatBitsToUint(s.stroke.y);
}

uint PathSeg_tag(PathSegRef ref) {
    return pathseg[ref.offset >> 2];
}

PathFillLine PathSeg_FillLine_read(PathSegRef ref) {
    return PathFillLine_read(PathFillLineRef(ref.offset + 4));
}

PathStrokeLine PathSeg_StrokeLine_read(PathSegRef ref) {
    return PathStrokeLine_read(PathStrokeLineRef(ref.offset + 4));
}

void PathSeg_Nop_write(PathSegRef ref) {
    pathseg[ref.offset >> 2] = PathSeg_Nop;
}

void PathSeg_FillLine_write(PathSegRef ref, PathFillLine s) {
    pathseg[ref.offset >> 2] = PathSeg_FillLine;
    PathFillLine_write(PathFillLineRef(ref.offset + 4), s);
}

void PathSeg_StrokeLine_write(PathSegRef ref, PathStrokeLine s) {
    pathseg[ref.offset >> 2] = PathSeg_StrokeLine;
    PathStrokeLine_write(PathStrokeLineRef(ref.offset + 4), s);
}
