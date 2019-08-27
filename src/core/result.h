//
// Created by Maksim Ruts on 2019-08-26.
//

#ifndef INC_2D_GAME_RESULT_H
#define INC_2D_GAME_RESULT_H

#include <type_traits>

namespace sc2d
{

    enum class ResErr
    {
        DAT_ERROR,
        OMG_WTF,
        SORRY_NOT_TODAY
    };

    // TODO: Make some sort of exception handling with registers crash data writing like in WebKit project
    template <typename T, ResErr E>
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
            else
                return {};
        }

        constexpr T& get() &
        {
            if(has)
                return result;
            else
                return {};
        }

        constexpr const T&& get() const&&
        {
            if(has)
                return std::move(result);
            else
                return {};
        }

        constexpr T&& get() &&
        {
            if(has)
                return std::move(result);
            else
                return {};
        }

        constexpr ResErr err()
        {
            if(!has)
                return error;
            else
                return {};
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

        constexpr explicit operator const char*() const
        {
            switch(error) {
            case ResErr::DAT_ERROR:
                return "DAT_ERROR";
            case ResErr::OMG_WTF:
                return "OMG_WTF";
            case ResErr::SORRY_NOT_TODAY:
                return "SORRY_NOT_TODAY";
            }
        }

    private:
        union
        {
            T result;
            ResErr error;
        };

        bool has;
    };
}
#endif //INC_2D_GAME_RESULT_H
