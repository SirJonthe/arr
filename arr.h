/// @file
/// @author github.com/SirJonthe
/// @date 2023
/// @copyright Public domain.
/// @license CC0 1.0

#ifndef CC0_ARR_H_INCLUDED__
#define CC0_ARR_H_INCLUDED__

#include <cstdint>

namespace cc0
{

	// TODO: values may not be necessary if array<type,size> can be a substitute.

	/// @brief A type of array mainly used for direct assignment in the other array types.
	/// @tparam type_t The type of the value array.
	/// @tparam size_u The number of elements in the value array.
	template < typename type_t, uint64_t size_u >
	struct values
	{
		type_t v[size_u]; // The memory holding the values.

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator type_t*( void );
		
		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator const type_t*( void ) const;
	};

	/// @brief A view into an existing array or slice. Slices do not own data - they only provide a view into it, in full or in part. This means that the programmer is responsible for ensuring that the data the slice is viewing is valid when being viewed, e.g. not our of scope or otherwise deleted. Elements in a slice can be manipulated, but the topography of the array itself can not be modified from within a slice even though subsets of the slice can be returned (create slices with smaller range from another slice).
	/// @warning Returning superset slices (larger bounds than what the underlying array or slice are defined for) should be considered undefined behavior.
	/// @tparam type_t The type of the array.
	template < typename type_t >
	class slice
	{
	protected:
		type_t   *m_values;
		uint64_t  m_size;
	
	public:
		/// @brief Default constructor. Sets data reference to null and size to zero.
		slice( void );

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy the reference of.
		template < typename type2_t >
		slice(const slice<type2_t> &arr);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy the reference of.
		template < typename type2_t >
		slice(const slice<const type2_t> &arr);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param values The array to reference.
		/// @param size The size of the array to reference.
		template < typename type2_t >
		slice(type2_t *values, uint64_t size);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param values The array to reference.
		/// @param size The size of the array to reference.
		template < typename type2_t >
		slice(const type2_t *values, uint64_t size);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to reference.
		/// @param values The array to reference.
		template < typename type2_t, uint64_t size_u >
		slice(type2_t (&values)[size_u]);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to reference.
		/// @param values The array to reference.
		template < typename type2_t, uint64_t size_u >
		slice(const type2_t (&values)[size_u]);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy the reference of.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		slice &operator=(const slice<type2_t> &arr);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy the reference of.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		slice &operator=(const slice<const type2_t> &arr);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to reference.
		/// @param values The array to copy the reference of.
		/// @return A reference to the object being assigned.
		template < typename type2_t, uint64_t size_u >
		slice &operator=(type2_t (&values)[size_u]);

		/// @brief Copies a reference to another array of a different type in order to allow for implicit convertion between array types, e.g. float to int array, or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to reference.
		/// @param values The array to copy the reference of.
		/// @return A reference to the object being assigned.
		template < typename type2_t, uint64_t size_u >
		slice &operator=(const type2_t (&values)[size_u]);

		/// @brief Releases the reference to an existing array.
		void release( void );

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator type_t*( void );

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator const type_t*( void ) const;

		/// @brief Implicitly converts the slice into a readonly slice.
		/// @tparam type2_t The other type.
		/// @return The const version of the slice. 
		template < typename type2_t >
		operator slice<const type2_t>( void ) const;

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<type_t> operator()(uint64_t start, uint64_t end);

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<const type_t> operator()(uint64_t start, uint64_t end) const;

		/// @brief Gets the size of the array.
		/// @return The number of elements in the array.
		uint64_t size( void ) const;
	};

	/// @brief A fixed-size array.
	/// @tparam type_t The type of the array.
	/// @tparam size_u The number of elements in the array.
	template < typename type_t, uint64_t size_u = 0 >
	class array
	{
	private:
		type_t m_values[size_u];

	private:
		/// @brief Copies memory into the object.
		/// @tparam type2_t The type of the memory to copy.
		/// @param values The values to copy.
		template < typename type2_t >
		void copy(const type2_t *values);

	public:
		/// @brief The default constructor. Does nothing. Does not initialize array elements.
		array( void ) = default;

		/// @brief Copies a given array of identical type and size.
		/// @param NA The array to copy.
		array(const array<type_t,size_u>&) = default;

		/// @brief Copies a given array of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param arr The array to copy.
		template < typename type2_t >
		array(const array<type2_t,size_u> &arr);

		/// @brief Copies a given array of values of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param values The array of values to copy.
		template < typename type2_t >
		array(const type2_t (&values)[size_u]);

		/// @brief Copies a given array of values of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param vals The array of values to copy.
		template < typename type2_t >
		array(const values<type2_t,size_u> &vals);

		/// @brief Copies a given array of identical type and size.
		/// @param NA The array to copy.
		/// @return A reference to the object being assigned.
		array &operator=(const array<type_t,size_u>&) = default;

		/// @brief Copies a given array of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param arr The array to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(const array<type2_t,size_u> &arr);

		/// @brief Copies a given array of values of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param vals The array of values to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(const values<type2_t,size_u> &vals);

		/// @brief Copies a given array of values of identical size, but of different type that can be converted to the target type. Allows copying e.g. a float array into an int array, or an array of pointers to derived objects to pointers of base class objects.
		/// @tparam type2_t The second type.
		/// @param values The array of values to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(const type2_t (&values)[size_u]);

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator type_t*( void );

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator const type_t*( void ) const;

		/// @brief Converts the array into a slice covering the full span of the array.
		/// @tparam type2_t The other type.
		/// @return The slice.
		template < typename type2_t >
		operator slice<type2_t>( void );

		/// @brief Converts the array into a slice covering the full span of the array.
		/// @return The slice.
		operator slice<type_t>( void );

		/// @brief Converts the array into a read-only slice covering the full span of the array.
		/// @tparam type2_t The other type.
		/// @return The slice.
		template < typename type2_t >
		operator const slice<const type2_t>( void ) const;

		/// @brief Converts the array into a read-only slice covering the full span of the array.
		/// @return The slice.
		operator const slice<const type_t>( void ) const;

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<type_t> operator()(uint64_t start, uint64_t end);

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<const type_t> operator()(uint64_t start, uint64_t end) const;

		/// @brief Gets the size of the array.
		/// @return The number of elements in the array.
		uint64_t size( void ) const;
	};

	/// @brief A variable-size array.
	/// @tparam type_t The type of the array.
	template < typename type_t >
	class array<type_t,0>
	{
	private:
		type_t   *m_values;
		uint64_t  m_size;
		uint64_t  m_capacity;

	private:
		/// @brief Copies memory into the object.
		/// @tparam type2_t The type of the memory to copy.
		/// @param values The values to copy.
		/// @param size The size of the array to copy.
		/// @param use_pool Determine if the array should pool memory if the size is less than the capacity of the array.
		template < typename type2_t >
		void copy(const type2_t *values, uint64_t size, bool use_pool);

	public:
		/// @brief Default contstructor. Sets the array memory to null, and size to 0.
		array( void );

		/// @brief Moves data from one array of one type to another.
		/// @tparam type2_t The other type.
		/// @param arr The other array.
		template < typename type2_t >
		array(array<type2_t> &&arr);

		/// @brief Moves data from one array to another.
		/// @param arr The other array.
		array(array<type_t> &&arr);

		/// @brief Allocate new memory for the array given a new size.
		/// @param size The number of elements in the newly created array.
		explicit array(uint64_t size);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy.
		template < typename type2_t >
		array(const array<type2_t> &arr);

		/// @brief Copies an array.
		/// @param arr The array to copy.
		array(const array<type_t> &arr);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy.
		template < typename type2_t, uint64_t size_u >
		array(const array<type2_t,size_u> &arr);

		/// @brief Copies a slice of an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array slice to copy.
		template < typename type2_t >
		array(const slice<type2_t> &arr);

		/// @brief Copies a slice of an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array slice to copy.
		template < typename type2_t >
		array(const slice<const type2_t> &arr);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param values The array to copy.
		/// @param size The size of the array to copy.
		template < typename type2_t >
		array(const type2_t *values, uint64_t size);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to copy.
		/// @param values The array to copy.
		template < typename type2_t, uint64_t size_u >
		array(const type2_t (&values)[size_u]);

		/// @brief Copies an array of values of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array of values to copy.
		/// @param vals The array of values to copy.
		template < typename type2_t, uint64_t size_u >
		array(const values<type2_t,size_u> &vals);

		/// @brief Frees allocated memory.
		~array( void );

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(const array<type2_t> &arr);

		/// @brief Copies an array.
		/// @param arr The array to copy.
		/// @return A reference to the object being assigned.
		array &operator=(const array<type_t> &arr);

		/// @brief Moves data from one array of one type to another.
		/// @tparam type2_t The other type.
		/// @param arr The other array.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(array<type2_t> &&arr);

		/// @brief Moves data from one array to another.
		/// @param arr The other array.
		/// @return A reference to the object being assigned.
		array &operator=(array<type_t> &&arr);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t, uint64_t size_u >
		array &operator=(const array<type2_t,size_u> &arr);

		/// @brief Copies a slice of an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @param arr The array slice to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t >
		array &operator=(const slice<const type2_t> &arr);

		/// @brief Copies an array of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array to copy.
		/// @param values The array to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t, uint64_t size_u >
		array &operator=(const type2_t (&values)[size_u]);

		/// @brief Copies an array of values of a potentially different type, allowing for implicit conversions e.g. int to float array or derived class pointer to base class pointer.
		/// @tparam type2_t The other type.
		/// @tparam size_u The size of the array of values to copy.
		/// @param vals The array of values to copy.
		/// @return A reference to the object being assigned.
		template < typename type2_t, uint64_t size_u >
		array &operator=(const values<type2_t,size_u> &vals);

		/// @brief Allocate new memory for the array given a new size.
		/// @param size The number of elements in the newly created array.
		/// @param use_pool Determine if the array should pool memory if the size is less than the capacity of the array.
		void create(uint64_t size, bool use_pool = true);

		/// @brief Frees allocated memory and sets the array size to 0.
		/// @param use_pool Only sets the size of the array to zero without actually freeing the underlying memory.
		void destroy(bool use_pool = true);

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator type_t*( void );

		/// @brief Allows direct access to the value array.
		/// @return The pointer to the array data.
		operator const type_t*( void ) const;

		/// @brief Converts the array into a slice covering the full span of the array.
		/// @tparam type2_t The other type.
		/// @return The slice.
		template < typename type2_t >
		operator slice<type2_t>( void );

		/// @brief Converts the array into a slice covering the full span of the array.
		/// @return The slice.
		operator slice<type_t>( void );

		/// @brief Converts the array into a read-only slice covering the full span of the array.
		/// @tparam type2_t The other type.
		/// @return The slice.
		template < typename type2_t >
		operator const slice<const type2_t>( void ) const;

		/// @brief Converts the array into a read-only slice covering the full span of the array.
		/// @return The slice.
		operator const slice<const type_t>( void ) const;

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<type_t> operator()(uint64_t start, uint64_t end);

		/// @brief Provides a view of the array with the given index bounds.
		/// @param start The start index of the view (inclusive).
		/// @param end The end index of the view (non-inclusive).
		/// @return The slice view of the array.
		slice<const type_t> operator()(uint64_t start, uint64_t end) const;

		/// @brief Gets the size of the array.
		/// @return The number of elements in the array.
		uint64_t size( void ) const;
	};

	/// @brief Selects a part of the input array and returns a slice within the specified
	/// @tparam type_t The type of the returned slice.
	/// @tparam type2_t The type of the input array.
	/// @param values The input array.
	/// @param start The first index (inclusive) of the view into the input array.
	/// @param end The last index (non-inclusive) of the view into the input array.
	/// @return A slice of the input array.
	template < typename type_t, typename type2_t >
	slice<type_t> view(type2_t *values, uint64_t start, uint64_t end);

	/// @brief Selects a part of the input array and returns a slice within the specified
	/// @tparam type_t The type of the returned slice.
	/// @tparam type2_t The type of the input array.
	/// @param values The input array.
	/// @param start The first index (inclusive) of the view into the input array.
	/// @param end The last index (non-inclusive) of the view into the input array.
	/// @return A slice of the input array.
	template < typename type_t, typename type2_t >
	slice<const type_t> view(const type2_t *values, uint64_t start, uint64_t end);

	/// @brief Selects a part of the input array and returns a slice within the specified
	/// @tparam type_t The type of the returned slice.
	/// @tparam type2_t The type of the input array.
	/// @param values The input array.
	/// @param count The number of elements in the array (or part thereof).
	/// @return A slice of the input array.
	template < typename type_t, typename type2_t >
	slice<type_t> view(type2_t *values, uint64_t count);

	/// @brief Selects a part of the input array and returns a slice within the specified
	/// @tparam type_t The type of the returned slice.
	/// @tparam type2_t The type of the input array.
	/// @param values The input array.
	/// @param count The number of elements in the array (or part thereof).
	/// @return A slice of the input array.
	template < typename type_t, typename type2_t >
	slice<const type_t> view(const type2_t *values, uint64_t count);

	/// @brief Writes a given value to the entirety of the slice.
	/// @tparam type_t 
	/// @param slice The slice to write the value to.
	/// @param value The value to write to the slice.
	template < typename type_t >
	void fill(slice<type_t> &slice, const type_t &value);
}

template < typename type_t, uint64_t size_u >
cc0::values<type_t,size_u>::operator type_t*( void )
{
	return v;
}

template < typename type_t, uint64_t size_u >
cc0::values<type_t,size_u>::operator const type_t*( void ) const
{
	return v;
}

template < typename type_t >
cc0::slice<type_t>::slice( void ) : m_values(nullptr), m_size(0)
{}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t>::slice(const cc0::slice<type2_t> &arr) : m_values(arr), m_size(arr.size())
{}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t>::slice(const cc0::slice<const type2_t> &arr) : m_values(arr), m_size(arr.size())
{}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t>::slice(type2_t *values, uint64_t size) : m_values(values), m_size(size)
{}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t>::slice(const type2_t *values, uint64_t size) : m_values(values), m_size(size)
{}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::slice<type_t>::slice(type2_t (&values)[size_u]) : m_values(values), m_size(size_u)
{}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::slice<type_t>::slice(const type2_t (&values)[size_u]) : m_values(values), m_size(size_u)
{}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t> &cc0::slice<type_t>::operator=(const slice<type2_t> &arr)
{
	m_values = arr.m_values;
	m_size = arr.m_size;
	return *this;
}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t> &cc0::slice<type_t>::operator=(const slice<const type2_t> &arr)
{
	m_values = arr.m_values;
	m_size = arr.m_size;
	return *this;
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::slice<type_t> &cc0::slice<type_t>::operator=(type2_t (&values)[size_u])
{
	m_values = values;
	m_size = size_u;
	return *this;
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::slice<type_t> &cc0::slice<type_t>::operator=(const type2_t (&values)[size_u])
{
	m_values = values;
	m_size = size_u;
	return *this;
}

template < typename type_t >
void cc0::slice<type_t>::release( void )
{
	m_values = nullptr;
	m_size = 0;
}

template < typename type_t >
cc0::slice<type_t>::operator type_t*( void )
{
	return m_values;
}

template < typename type_t >
cc0::slice<type_t>::operator const type_t*( void ) const
{
	return m_values;
}

template < typename type_t >
cc0::slice<type_t> cc0::slice<type_t>::operator()(uint64_t start, uint64_t end)
{
	return slice<type_t>(m_values + start, (end - start));
}

template < typename type_t >
cc0::slice<const type_t> cc0::slice<type_t>::operator()(uint64_t start, uint64_t end) const
{
	return slice<const type_t>(m_values + start, (end - start));
}

template < typename type_t >
uint64_t cc0::slice<type_t>::size( void ) const
{
	return m_size;
}

template < typename type_t >
template < typename type2_t >
cc0::slice<type_t>::operator slice<const type2_t>( void ) const {
	return slice<const type2_t>(m_values, m_size);
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
void cc0::array<type_t,size_u>::copy(const type2_t *values)
{
	for (uint64_t i = 0; i < size_u; ++i) {
		m_values[i] = values[i];
	}
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u>::array(const cc0::array<type2_t,size_u> &arr)
{
	copy<type2_t>(arr);
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u>::array(const type2_t (&values)[size_u])
{
	copy(values);
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u>::array(const cc0::values<type2_t,size_u> &vals)
{
	copy(vals.v);
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u> &cc0::array<type_t,size_u>::operator=(const cc0::array<type2_t,size_u> &arr)
{
	copy<type2_t>(arr);
	return *this;
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u> &cc0::array<type_t,size_u>::operator=(const cc0::values<type2_t,size_u> &vals)
{
	copy(vals.v);
	return *this;
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u> &cc0::array<type_t,size_u>::operator=(const type2_t (&values)[size_u])
{
	copy(values);
	return *this;
}

template < typename type_t, uint64_t size_u >
cc0::array<type_t,size_u>::operator type_t*( void )
{
	return m_values;
}

template < typename type_t, uint64_t size_u >
cc0::array<type_t,size_u>::operator const type_t*( void ) const
{
	return m_values;
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u>::operator cc0::slice<type2_t>( void )
{
	return cc0::slice<type2_t>(m_values);
}

template < typename type_t, uint64_t size_u >
cc0::array<type_t,size_u>::operator cc0::slice<type_t>( void )
{
	return cc0::slice<type_t>(m_values);
}

template < typename type_t, uint64_t size_u >
template < typename type2_t >
cc0::array<type_t,size_u>::operator const cc0::slice<const type2_t>( void ) const
{
	return cc0::slice<const type2_t>(m_values);
}

template < typename type_t, uint64_t size_u >
cc0::array<type_t,size_u>::operator const cc0::slice<const type_t>( void ) const
{
	return cc0::slice<const type_t>(m_values);
}

template < typename type_t, uint64_t size_u >
cc0::slice<type_t> cc0::array<type_t,size_u>::operator()(uint64_t start, uint64_t end)
{
	return slice<type_t>(m_values + start, (end - start));
}

template < typename type_t, uint64_t size_u >
cc0::slice<const type_t> cc0::array<type_t,size_u>::operator()(uint64_t start, uint64_t end) const
{
	return slice<const type_t>(m_values + start, (end - start));
}

template < typename type_t, uint64_t size_u >
uint64_t cc0::array<type_t,size_u>::size( void ) const
{
	return size_u;
}

template < typename type_t >
template < typename type2_t >
void cc0::array<type_t>::copy(const type2_t *values, uint64_t size, bool use_pool)
{
	create(size, use_pool);
	for (uint64_t i = 0; i < m_size; ++i) {
		m_values[i] = values[i];
	}
}

template < typename type_t >
cc0::array<type_t>::array( void ) : m_values(nullptr), m_size(0), m_capacity(0)
{}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t>::array(const type2_t (&values)[size_u]) : array()
{
	copy<type2_t>(values, size_u, false);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::array(cc0::array<type2_t> &&arr) : m_values(arr), m_size(arr.m_size), m_capacity(arr.m_capacity)
{
	arr.m_values = nullptr;
	arr.m_size = 0;
	arr.m_capacity = 0;
}

template < typename type_t >
cc0::array<type_t>::array(cc0::array<type_t> &&arr) : m_values(arr), m_size(arr.m_size), m_capacity(arr.m_capacity)
{
	arr.m_values = nullptr;
	arr.m_size = 0;
	arr.m_capacity = 0;
}

template < typename type_t >
cc0::array<type_t>::array(uint64_t size) : array()
{
	create(size, false);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::array(const cc0::array<type2_t> &arr) : array()
{
	copy<type2_t>(arr, arr.size(), true);
}

template < typename type_t >
cc0::array<type_t>::array(const cc0::array<type_t> &arr) : array()
{
	copy<type_t>(arr, arr.size(), true);
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t>::array(const cc0::array<type2_t,size_u> &arr) : array()
{
	copy<type2_t>(arr, size_u, true);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::array(const cc0::slice<type2_t> &arr) : array()
{
	copy<type2_t>(arr, arr.size(), true);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::array(const cc0::slice<const type2_t> &arr) : array()
{
	copy<type2_t>(arr, arr.size(), true);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::array(const type2_t *values, uint64_t size) : array()
{
	copy<type2_t>(values, size, true);
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t>::array(const cc0::values<type2_t,size_u> &vals) : array()
{
	copy<type2_t>(vals.v, size_u, true);
}

template < typename type_t >
cc0::array<type_t>::~array( void )
{
	delete [] m_values;
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t> &cc0::array<type_t>::operator=(const cc0::array<type2_t> &arr)
{
	copy<type2_t>(arr, arr.size(), true);
	return *this;
}

template < typename type_t >
cc0::array<type_t> &cc0::array<type_t>::operator=(const cc0::array<type_t> &arr)
{
	copy<type_t>(arr, arr.size(), true);
	return *this;
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t> &cc0::array<type_t>::operator=(cc0::array<type2_t> &&arr)
{
	if (m_values != arr.m_values) {
		destroy(false);
	}
	m_values       = arr.m_values;
	m_size         = arr.m_size;
	m_capacity     = arr.m_capacity;
	arr.m_values   = nullptr;
	arr.m_size     = 0;
	arr.m_capacity = 0;
	return *this;
}

template < typename type_t >
cc0::array<type_t> &cc0::array<type_t>::operator=(cc0::array<type_t> &&arr)
{
	if (m_values != arr.m_values) {
		destroy(false);
	}
	m_values       = arr.m_values;
	m_size         = arr.m_size;
	m_capacity     = arr.m_capacity;
	arr.m_values   = nullptr;
	arr.m_size     = 0;
	arr.m_capacity = 0;
	return *this;
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t> &cc0::array<type_t>::operator=(const cc0::array<type2_t,size_u> &arr)
{
	copy<type2_t>(arr, size_u, true);
	return *this;
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t> &cc0::array<type_t>::operator=(const cc0::slice<const type2_t> &arr)
{
	copy<type2_t>(arr, arr.size(), true);
	return *this;
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t> &cc0::array<type_t>::operator=(const type2_t (&values)[size_u])
{
	copy<type2_t>(values, size_u, true);
	return *this;
}

template < typename type_t >
template < typename type2_t, uint64_t size_u >
cc0::array<type_t> &cc0::array<type_t>::operator=(const cc0::values<type2_t,size_u> &vals)
{
	copy(vals.v, size_u, true);
	return *this;
}

template < typename type_t >
void cc0::array<type_t>::create(uint64_t size, bool use_pool)
{
	if ((size < m_capacity && !use_pool) || size > m_capacity) {
		destroy(false);
		if (size > 0) {
			m_values = new type_t[size];
			m_size = m_capacity = size;
		}
	}
}

template < typename type_t >
void cc0::array<type_t>::destroy(bool use_pool)
{
	if (!use_pool) {
		delete [] m_values;
		m_values = nullptr;
		m_capacity = 0;
	}
	m_size = 0;
}

template < typename type_t >
cc0::array<type_t>::operator type_t*( void )
{
	return m_values;
}

template < typename type_t >
cc0::array<type_t>::operator const type_t*( void ) const
{
	return m_values;
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::operator cc0::slice<type2_t>( void )
{
	return cc0::slice<type2_t>(m_values, m_size);
}

template < typename type_t >
cc0::array<type_t>::operator cc0::slice<type_t>( void )
{
	return cc0::slice<type_t>(m_values, m_size);
}

template < typename type_t >
template < typename type2_t >
cc0::array<type_t>::operator const cc0::slice<const type2_t>( void ) const
{
	return cc0::slice<const type2_t>(m_values, m_size);
}

template < typename type_t >
cc0::array<type_t>::operator const cc0::slice<const type_t>( void ) const
{
	return cc0::slice<const type_t>(m_values, m_size);
}

template < typename type_t >
cc0::slice<type_t> cc0::array<type_t>::operator()(uint64_t start, uint64_t end)
{
	return cc0::slice<type_t>(m_values + start, (end - start));
}

template < typename type_t >
cc0::slice<const type_t> cc0::array<type_t>::operator()(uint64_t start, uint64_t end) const
{
	return cc0::slice<const type_t>(m_values + start, (end - start));
}

template < typename type_t >
uint64_t cc0::array<type_t>::size( void ) const
{
	return m_size;
}

template < typename type_t, typename type2_t >
cc0::slice<type_t> cc0::view(type2_t *values, uint64_t start, uint64_t end)
{
	return cc0::slice<type_t>(values + start, (end - start));
}

template < typename type_t, typename type2_t >
cc0::slice<const type_t> cc0::view(const type2_t *values, uint64_t start, uint64_t end)
{
	return cc0::slice<const type_t>(values + start, (end - start));
}

template < typename type_t, typename type2_t >
cc0::slice<type_t> cc0::view(type2_t *values, uint64_t count)
{
	return cc0::slice<type_t>(values, count);
}

template < typename type_t, typename type2_t >
cc0::slice<const type_t> cc0::view(const type2_t *values, uint64_t count)
{
	return cc0::slice<const type_t>(values, count);
}

template < typename type_t >
void cc0::fill(cc0::slice<type_t> &slice, const type_t &value)
{
	for (uint64_t i = 0; i < slice.size(); ++i) {
		slice[i] = value;
	}
}

#endif
