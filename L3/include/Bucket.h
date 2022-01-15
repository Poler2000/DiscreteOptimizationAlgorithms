//
// Created by pawel on 12.12.2021.
//

#ifndef L3_BUCKET_H
#define L3_BUCKET_H

struct Bucket {
    long minLabel;
    long maxLabel;
    std::vector<std::list<int>> content;
    size_t elements = 0;
};

struct Bucket2 {
    long minLabel;
    long maxLabel;
    std::list<int> content;
    size_t elements = 0;
};


#endif //L3_BUCKET_H
