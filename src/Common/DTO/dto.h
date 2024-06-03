#ifndef DTO_H_
#define DTO_H_

#include "../Types/dto.h"

class DTO {
public:
    virtual DTOType getType() const = 0;
};

#endif  // DTO_H_
