#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libprovider/archive_reader.hpp"
#include "libprovider/resource.hpp"

namespace provider
{
  struct archive_reader_impl_s
  {
    archive_reader_impl_s ();
    ~archive_reader_impl_s (); 

    int                      m_file;
    util::file_size_t        m_fsize;
    std::vector <resource_c> m_resources;
  };
  // ---------------------------------------------------------------------------------------
  archive_reader_impl_s::archive_reader_impl_s ()
    : m_file (-1),
      m_fsize (0)
  {
  }
  // ---------------------------------------------------------------------------------------
  archive_reader_impl_s::~archive_reader_impl_s ()
  {
    if (m_file != -1)
      {
	::close (m_file);
      }
  }
  // ========================================================================================
  archive_reader_c::archive_reader_c ()
  {
    m_pimpl = new archive_reader_impl_s;
  }
  // ---------------------------------------------------------------------------------------
  archive_reader_c::~archive_reader_c ()
  {
    delete m_pimpl;
  }
  // ---------------------------------------------------------------------------------------
  bool archive_reader_c::open (const char* path)
  {
    m_pimpl->m_file = ::open (path, O_RDONLY);
    if (m_pimpl->m_file == -1)
      {
	return false;
      }
    m_pimpl->m_fsize = lseek (m_pimpl->m_file, 0, SEEK_END);
    lseek (m_pimpl->m_file, 0, SEEK_SET);
    while (true)
      {
	std::string       name;
	util::file_size_t size;
	util::file_size_t offset;
	bool rc = this->_get_next_resource (name, size, offset);
	if (!rc)
	  {
	    break;
	  }
	m_pimpl->m_resources.push_back (resource_c (name, size, offset));
      }
    return true;
  }
  // ---------------------------------------------------------------------------------------
  std::size_t archive_reader_c::number_of_resouces () const
  {
    return m_pimpl->m_resources.size ();
  }
  // ---------------------------------------------------------------------------------------
  bool archive_reader_c::describe_resource (std::size_t resource_number, resource_c& resource)
  {
    if (resource_number < number_of_resouces ())
      {
	resource = m_pimpl->m_resources [resource_number];
	return true;
      }
    return false;
  }
  // ---------------------------------------------------------------------------------------
  char* archive_reader_c::load (const resource_c& resource)
  {
    if (!resource.valid ())
      {
	return 0;
      }
    const util::file_size_t curr_pos = lseek (m_pimpl->m_file, 0, SEEK_CUR);
    if (curr_pos == -1)
      {
	return 0;
      }
    if (lseek (m_pimpl->m_file, resource.offset (), SEEK_SET) == -1)
      {
	return 0;
      }
    const util::file_size_t sz = resource.size ();
    char* buff = new char [sz];
    if (this->_read (buff, sz) != sz)
      {
	delete [] buff;
	return 0;
      }
    if (lseek (m_pimpl->m_file, curr_pos, SEEK_SET) == -1)
      {
	delete [] buff;
	return 0;
      }
    return buff;
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (char* buff, std::size_t size)
  {
    return ::read (m_pimpl->m_file, buff, size);
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::sint8_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::uint8_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::sint16_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::uint16_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::sint32_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::ssize_t archive_reader_c::_read (util::uint32_t& v)
  {
    return ::read (m_pimpl->m_file, (char*)&v, sizeof (v));
  }
  // ---------------------------------------------------------------------------------------
  util::file_size_t archive_reader_c::_file_size () const
  {
    return m_pimpl->m_fsize;
  }
  // ---------------------------------------------------------------------------------------
  util::file_size_t archive_reader_c::_seek (util::file_size_t pos)
  {
    return lseek (m_pimpl->m_file, pos, SEEK_SET);
  }
    
  
}