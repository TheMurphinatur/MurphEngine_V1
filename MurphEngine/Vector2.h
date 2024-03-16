#pragma once

namespace MurphEngine
{
    template<typename DataType>
    struct Vector2
    {
        Vector2(DataType x, DataType y)
            : m_x(x)
            , m_y(y)
        {
            
        }
        DataType m_x = 0;
        DataType m_y = 0;

        DataType GetX() const { return m_x; }
        DataType GetY() const { return m_y; }
        void SetX(DataType x) { m_x = x; }
        void SetY(DataType y) { m_y = y; }
    };

    template<typename DataType>
    struct Vector3
    {
        DataType m_x = 0;
        DataType m_y = 0;
        DataType m_z = 0;

        
        DataType GetX() const { return m_x; }
        DataType GetY() const { return m_y; }
        DataType GetZ() const { return m_z; }

        void SetX(DataType x) { m_x = x; }
        void SetY(DataType y) { m_y = y; }
        void SetZ(DataType z) { m_x = z; }

    };

    

}

