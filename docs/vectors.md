## Members

# structs for vector `math::vec2 / math::vec3 / math::vec4` 



## Summary (for vector2)

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`x`](#structmath_1_1vec2_1a80b10d5dce55f531250dc88c9afd2d2b) | 
`public float `[`y`](#structmath_1_1vec2_1aec0b4a209674ce9a5fba6f76f514f777) | 
`public inline  `[`vec2`](#structmath_1_1vec2_1a4ee399d6f002c4ec24f406e04d52e281)`()` | 
`public inline  `[`vec2`](#structmath_1_1vec2_1a7c9641e308af00f8e875de6cd07da88e)`(float x,float y)` | 
`public inline float & `[`operator[]`](#structmath_1_1vec2_1a1ffee39907a0aa106ac5b8a5faa3d7b0)`(int i)` | Gets element as array 
`public inline const float & `[`operator[]`](#structmath_1_1vec2_1a62d6627cb78093fe11107ea52c284583)`(int i) const` | Gets element as array 
`public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator *=`](#structmath_1_1vec2_1a680ce485188cc1b0f21cc64fac5fe447)`(float s)` | Multiplication by scalar 
`public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator/=`](#structmath_1_1vec2_1a5a1153001cba3493edd3a2d8d6060ae2)`(float s)` | Division by scalar 
`public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator+=`](#structmath_1_1vec2_1af99deb7c62b5c3e494854e6ba83f7422)`(const `[`vec2`](#structmath_1_1vec2)` & v)` | Addition by other vector2 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator-=`](#structmath_1_1vec2_1a9c6705809a9bfa54e6cde070f10a4984)`(const `[`vec2`](#structmath_1_1vec2)` & v)` | Subtraction by other vector2 

## Members

#### `public float `[`x`](#structmath_1_1vec2_1a80b10d5dce55f531250dc88c9afd2d2b) 

#### `public float `[`y`](#structmath_1_1vec2_1aec0b4a209674ce9a5fba6f76f514f777) 

#### `public inline  `[`vec2`](#structmath_1_1vec2_1a4ee399d6f002c4ec24f406e04d52e281)`()` 

#### `public inline  `[`vec2`](#structmath_1_1vec2_1a7c9641e308af00f8e875de6cd07da88e)`(float x,float y)` 

#### `public inline float & `[`operator[]`](#structmath_1_1vec2_1a1ffee39907a0aa106ac5b8a5faa3d7b0)`(int i)` 

Gets element as array 
#### Parameters
* `i` index 

#### Returns
the element

#### `public inline const float & `[`operator[]`](#structmath_1_1vec2_1a62d6627cb78093fe11107ea52c284583)`(int i) const` 

Gets element as array 
#### Parameters
* `i` index 

#### Returns
the element

#### `public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator *=`](#structmath_1_1vec2_1a680ce485188cc1b0f21cc64fac5fe447)`(float s)` 

Multiplication by scalar 
#### Parameters
* `s` scalar 

#### Returns
current vector

#### `public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator/=`](#structmath_1_1vec2_1a5a1153001cba3493edd3a2d8d6060ae2)`(float s)` 

Division by scalar 
#### Parameters
* `s` scalar 

#### Returns
current vector

#### `public inline `[`vec2`](#structmath_1_1vec2)` & `[`operator+=`](#structmath_1_1vec2_1af99deb7c62b5c3e494854e6ba83f7422)`(const `[`vec2`](#structmath_1_1vec2)` & v)` 

Addition by other vector2 
#### Parameters
* `v` some vector2 

#### Returns
current vector

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator-=`](#structmath_1_1vec2_1a9c6705809a9bfa54e6cde070f10a4984)`(const `[`vec2`](#structmath_1_1vec2)` & v)` 

Subtraction by other vector2 
#### Parameters
* `v` some vector2 

#### Returns
current vector

## Additional operations with vectors in `math` namespace

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------  
`public inline bool `[`operator==`](#namespacemath_1a3456527eba6606d605f25d01db67a921)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Compares two vectors 
`public inline bool `[`operator!=`](#namespacemath_1a6eb9f8aab29175369238ad875261e6e3)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Compares two vectors 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator *`](#namespacemath_1a072e661cefabf97e64f94d429aa13607)`(const `[`vec2`](#structmath_1_1vec2)` & v,float s)`            | Multiplication of vector by scalar 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator *`](#namespacemath_1a05fa057abc856fd760d0b293bf30b382)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Regular multiplication 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator/`](#namespacemath_1a16d49073076106b44f452b7b7550fd76)`(const `[`vec2`](#structmath_1_1vec2)` & v,float s)`            | Division of vector by scalar 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator+`](#namespacemath_1a3dbe67d4733a19991cf39ca186c85209)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | The sum of vectors 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`operator-`](#namespacemath_1a8e8171b9d634370e32cc25fae556b4bc)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | The difference of two vectors 
`public inline float `[`dot`](#namespacemath_1a93f7f9084e149e42193f7909ee99a2c7)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Scalar product between two vectors 
`public inline float `[`magnitude`](#namespacemath_1a51788ba9f4525d6bd45e411b7b186793)`(const `[`vec2`](#structmath_1_1vec2)` & v)`            | Lenght of the vector 
`public inline float `[`magnitudeSq`](#namespacemath_1ad2d695e6a1bd5f184c6221db9e2350a2)`(const `[`vec2`](#structmath_1_1vec2)` & v)`            | Square length of the vector 
`public inline float `[`distance`](#namespacemath_1a45f6d1075aaa2fc3a9c5acaf7c79116b)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Calculates distance between two vectors 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`normalize`](#namespacemath_1a40e2576eed9b3b236dbd701800f06cba)`(const `[`vec2`](#structmath_1_1vec2)` & v)`            | Vector normalization 
`public inline float `[`angle`](#namespacemath_1ade9fefbcc586a94034ae83f74177d00f)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)`            | Calculates angle between two vectors 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`project`](#namespacemath_1ae4e1e92d04d458a30682e2720dfee71a)`(const `[`vec2`](#structmath_1_1vec2)` & len,const `[`vec2`](#structmath_1_1vec2)` & dir)`            | Project one vector onto another 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`perpendicular`](#namespacemath_1ae8bb619a793429b0cf523beb2a84f92e)`(const `[`vec2`](#structmath_1_1vec2)` & len,const `[`vec2`](#structmath_1_1vec2)` & dir)`            | Calculates perpendicular vector 
`public inline `[`vec2`](#structmath_1_1vec2)` `[`reflection`](#namespacemath_1aa21ce35b4699217def78487e13ee6502)`(const `[`vec2`](#structmath_1_1vec2)` & v,const `[`vec2`](#structmath_1_1vec2)` & normal)`            | Calculates reflected vector  
`public inline `[`vec3`](#structmath_1_1vec3)` `[`cross`](#namespacemath_1aee2ac0ed9899f1feb7d90d5cbbb22747)`(const `[`vec3`](#structmath_1_1vec3)` & a,const `[`vec3`](#structmath_1_1vec3)` & b)`            | Calculates vector that is perpendicular to both a and b 

## Members  

#### `public inline bool `[`operator==`](#namespacemath_1a3456527eba6606d605f25d01db67a921)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Compares two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
true if vectors are equal

#### `public inline bool `[`operator!=`](#namespacemath_1a6eb9f8aab29175369238ad875261e6e3)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Compares two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
true if vectors are not equal

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator *`](#namespacemath_1a072e661cefabf97e64f94d429aa13607)`(const `[`vec2`](#structmath_1_1vec2)` & v,float s)` 

Multiplication of vector by scalar 
#### Parameters
* `v` some vector2 

* `s` some scalar 

#### Returns
copy of the calculation result

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator *`](#namespacemath_1a05fa057abc856fd760d0b293bf30b382)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Regular multiplication 
#### Parameters
* `a` 

* `b` 

#### Returns
copy of the calculation result

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator/`](#namespacemath_1a16d49073076106b44f452b7b7550fd76)`(const `[`vec2`](#structmath_1_1vec2)` & v,float s)` 

Division of vector by scalar 
#### Parameters
* `v` some vector2 

* `s` some scalar 

#### Returns
copy of the calculation result

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator+`](#namespacemath_1a3dbe67d4733a19991cf39ca186c85209)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

The sum of vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
copy of the calculation result

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`operator-`](#namespacemath_1a8e8171b9d634370e32cc25fae556b4bc)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

The difference of two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
copy of the calculation result

#### `public inline float `[`dot`](#namespacemath_1a93f7f9084e149e42193f7909ee99a2c7)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Scalar product between two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
scalar value

[https://en.wikipedia.org/wiki/Dot_product](https://en.wikipedia.org/wiki/Dot_product)

#### `public inline float `[`magnitude`](#namespacemath_1a51788ba9f4525d6bd45e411b7b186793)`(const `[`vec2`](#structmath_1_1vec2)` & v)` 

Lenght of the vector 
#### Parameters
* `v` 

#### Returns
scalar value

[https://en.wikipedia.org/wiki/Magnitude_(mathematics)#Vector_spaces](https://en.wikipedia.org/wiki/Magnitude_(mathematics)#Vector_spaces)

#### `public inline float `[`magnitudeSq`](#namespacemath_1ad2d695e6a1bd5f184c6221db9e2350a2)`(const `[`vec2`](#structmath_1_1vec2)` & v)` 

Square length of the vector 
#### Parameters
* `v` 

#### Returns
scalar value 

avoids expensive square root operation

#### `public inline float `[`distance`](#namespacemath_1a45f6d1075aaa2fc3a9c5acaf7c79116b)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Calculates distance between two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
scalar value

[https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions](https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions)

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`normalize`](#namespacemath_1a40e2576eed9b3b236dbd701800f06cba)`(const `[`vec2`](#structmath_1_1vec2)` & v)` 

Vector normalization 
#### Parameters
* `v` vector that will be normalized 

#### Returns
unit vector

[https://en.wikipedia.org/wiki/Unit_vector](https://en.wikipedia.org/wiki/Unit_vector)

#### `public inline float `[`angle`](#namespacemath_1ade9fefbcc586a94034ae83f74177d00f)`(const `[`vec2`](#structmath_1_1vec2)` & a,const `[`vec2`](#structmath_1_1vec2)` & b)` 

Calculates angle between two vectors 
#### Parameters
* `a` 

* `b` 

#### Returns
angle in radians

[https://en.wikipedia.org/wiki/Inner_product_space#Norms_on_inner_product_spaces](https://en.wikipedia.org/wiki/Inner_product_space#Norms_on_inner_product_spaces)

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`project`](#namespacemath_1ae4e1e92d04d458a30682e2720dfee71a)`(const `[`vec2`](#structmath_1_1vec2)` & len,const `[`vec2`](#structmath_1_1vec2)` & dir)` 

Project one vector onto another 
#### Parameters
* `len` 

* `dir` 

#### Returns
projected vector

[https://en.wikipedia.org/wiki/Vector_projection#Vector_projection_2](https://en.wikipedia.org/wiki/Vector_projection#Vector_projection_2)

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`perpendicular`](#namespacemath_1ae8bb619a793429b0cf523beb2a84f92e)`(const `[`vec2`](#structmath_1_1vec2)` & len,const `[`vec2`](#structmath_1_1vec2)` & dir)` 

Calculates perpendicular vector 
#### Parameters
* `len` 

* `dir` 

#### Returns

#### `public inline `[`vec2`](#structmath_1_1vec2)` `[`reflection`](#namespacemath_1aa21ce35b4699217def78487e13ee6502)`(const `[`vec2`](#structmath_1_1vec2)` & v,const `[`vec2`](#structmath_1_1vec2)` & normal)` 

Calculates reflected vector 
#### Parameters
* `v` 

* `normal` 

#### Returns
reflected vector v around normal  

[https://en.wikipedia.org/wiki/Reflection_(mathematics)](https://en.wikipedia.org/wiki/Reflection_(mathematics))  


#### `public inline `[`vec3`](#structmath_1_1vec3)` `[`cross`](#namespacemath_1aee2ac0ed9899f1feb7d90d5cbbb22747)`(const `[`vec3`](#structmath_1_1vec3)` & a,const `[`vec3`](#structmath_1_1vec3)` & b)` 

Calculates vector that is perpendicular to both a and b 
#### Parameters
* `a` 

* `b` 

#### Returns
copy of the calculation result

[https://en.wikipedia.org/wiki/Cross_product](https://en.wikipedia.org/wiki/Cross_product)

