//
// Created by Maksim Ruts on 2019-08-26.
//

#ifndef INC_2D_GAME_RESULT_H
#define INC_2D_GAME_RESULT_H

#include "os/error_types.h"
#include "os/terminate.h"
#include <type_traits>

namespace sc2d
{

    // TODO: Error types that will not terminate the program.
    // TODO: finally/scope guard
    template <typename T, typename E = sc2d::Err>
    class Result
    {
    public:
        constexpr Result(const E& err)
            : has(false)
        {
            if constexpr(std::is_same<sc2d::Err, E>::value)
                error = err;
            else
                new(&error) E(err);
        };

        constexpr Result(E&& err)
            : has(false)
        {
            if constexpr(std::is_same<sc2d::Err, E>::value)
                error = err;
            else
                new(&error) E(std::move(err));
        }

        constexpr Result(const T& value)
            : has(true)
        {
            new(&result) T(value);
        }

        constexpr Result(T&& value)
            : has(true)
        {
            new(&result) T(std::move(value));
        }

        constexpr Result(const Result& o)
            : has(o.has)
        {
            if(has) {
                new(&result) T(o.result);
            } else {
                if constexpr(std::is_same<sc2d::Err, E>::value)
                    error = o.error;
                else
                    new(&error) E(o.error);
            }
        }

        constexpr Result(Result&& o)
            : has(o.has)
        {
            if(has) {
                new(&result) T(std::move(o.result));
            } else {
                if constexpr(std::is_same<sc2d::Err, E>::value)
                    error = o.error;
                else
                    new(&error) E(std::move(o.error));
            }
        }

        ~Result()
        {
            if(has)
                result.~T();
            if constexpr(!std::is_same<sc2d::Err, E>::value) {
                if(!has)
                    error.~E();
            }
        }

        constexpr Result& operator=(const Result& o)
        {
            swap(o);
            return *this;
        }
        constexpr Result& operator=(Result&& o)
        {
            swap(std::move(o));
            return *this;
        }

        constexpr const T& val() const&
        {
            if(has)
                return result;
            return (sc2d::terminate(error), result);
        }

        constexpr T& val() &
        {
            if(has)
                return result;
            return (sc2d::terminate(error), result);
        }

        constexpr const T&& val() const&&
        {
            if(has)
                return std::move(result);
            return std::move((sc2d::terminate(error), result));
        }

        constexpr T&& val() &&
        {
            if(has)
                return std::move(result);
            return std::move((sc2d::terminate(error), result));
        }

        constexpr const E& err() const&
        {
            if(!has)
                return error;
            return (sc2d::terminate(Err::OK), error);
        }

        constexpr E& err() &
        {
            if(!has)
                return error;
            return (sc2d::terminate(Err::OK), error);
        }

        constexpr const E&& err() const&&
        {
            if(!has)
                return error;
            return std::move((sc2d::terminate(Err::OK), error));
        }

        constexpr E&& err() &&
        {
            if(!has)
                return error;
            return std::move((sc2d::terminate(Err::OK), error));
        }

        template <typename... Args>
        static Result success(Args&&... params)
        {
            Result r;
            r.has = true;
            new(&r.result) T(std::forward<Args>(params)...);
            return r;
        }

        // TODO: support different error types
        [[noreturn]] static Result throw_err(E e)
        {
            sc2d::terminate(e);
        };

        constexpr explicit operator bool() const
        {
            return has;
        }

    private:
        union
        {
            T result;
            E error;
        };

        bool has;

        void swap(Result& o)
        {
            using std::swap;
            if(has && o.has) {
                swap(has, o.has);
            } else if(has && !o.has) {
                E temp = std::move(o.error);
                o.error.~E();
                new(&o.error) E(error);
                result.~T();
                new(&error) E(std::move(temp));
                std::swap(has, o.has);
            } else if(!has && o.has) {
                o.swap(*this);
            } else {
                swap(error, o.error);
            }
        }
    };

    using ResultBool = Result<bool>;
}
#endif //INC_2D_GAME_RESULT_H
