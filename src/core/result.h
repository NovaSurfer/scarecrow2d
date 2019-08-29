//
// Created by Maksim Ruts on 2019-08-26.
//

#ifndef INC_2D_GAME_RESULT_H
#define INC_2D_GAME_RESULT_H

#include "os/terminate.h"
#include "os/error_types.h"
#include <type_traits>

namespace sc2d
{

    template <typename T, Err E>
    class Result
    {
    public:
        constexpr Result()
            : error(E)
            , has(false) {};

        constexpr Result(const T& value)
            : has(true)
        {
            new(&result) T(value);
        };

        constexpr Result(T&& value)
            : has(true)
        {
            new(&result) T(std::move(value));
        };

        constexpr Result(const Result& o)
            : has(o.has)
        {
            if(has) {
                new(&result) T(o.result);
            } else {
                error = o.error;
            }
        };

        constexpr Result(Result&& o)
            : has(o.has)
        {
            if(has) {
                new(&result) T(o.result);
            } else {
                error = o.error;
            }
        };

        ~Result()
        {
            if(has)
                result.~T();
        }

        //        constexpr Result& operator=(const Result& r)
        //        {
        //            r.swap(*this);
        //            return *this;
        //        };
        //        Result& operator=(Result&&);

        constexpr const T& get() const&
        {
            if(has)
                return result;
            return (sc2d::terminate(E), result);
        }

        constexpr T& get() &
        {
            if(has)
                return result;
            return (sc2d::terminate(E), result);
        }

        constexpr const T&& get() const&&
        {
            if(has)
                return std::move(result);
            return sc2d::terminate(E);
        }

        constexpr T&& get() &&
        {
            if(has)
                return std::move(result);
            return sc2d::terminate(E);
        }

        constexpr Err err()
        {
            if(!has)
                return error;
            return Err::OK;
        }

        template <typename... Args>
        static Result success(Args&&... params)
        {
            Result r;
            r.has = true;
            new(&r.result) T(std::forward<Args>(params)...);
            return r;
        }

        constexpr explicit operator bool() const
        {
            return has;
        }

    private:
        union
        {
            T result;
            Err error;
        };

        bool has;
    };
}
#endif //INC_2D_GAME_RESULT_H
