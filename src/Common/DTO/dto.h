#ifndef DTO_H_
#define DTO_H_

#include "../Types/dto.h"

class DTO {
public:
    virtual DTOType getType() const = 0;
    virtual std::unique_ptr<DTO> clone() const = 0;
    virtual ~DTO() = default;
};

#endif  // DTO_H_
