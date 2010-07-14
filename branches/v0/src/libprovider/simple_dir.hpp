#ifndef __LIBPROVIDER_SIMPLE_DIR_HPP__
#define __LIBPROVIDER_SIMPLE_DIR_HPP__

#include "libvfs/fs_dir.hpp"
#include "libvfs/inode_defs.hpp"

#include "libprovider/provider_export.hpp"

namespace provider
{
  struct simple_dir_impl_s;

  class LIBPROVIDER_API simple_dir_c : public vfs::fs_dir_c
  {
  public:
    enum operation_t
      {
	NO_DUBLICATES,
	ALLOW_DUBLICATES,
	IGNORE_DUBLICATES
      };
  public:
    simple_dir_c (vfs::fs_c* owner, 
		  vfs::inode_num_t parent_ino,
		  operation_t op); 
    virtual ~simple_dir_c ();
    virtual vfs::fs_object_c*   load_object (vfs::inode_num_t ino);
    virtual vfs::inode_num_t    parent_inode_num () const;
    virtual std::size_t         size      () const;
    virtual std::size_t read (std::size_t entry_num, std::string& name, 
			      vfs::inode_num_t& inode_num);
    virtual vfs::inode_num_t   lookup (const std::string& name) const;
  protected:
    bool _add_fs_object (vfs::fs_object_c* fs_obj, const std::string& name);
  private:
    simple_dir_impl_s* m_pimpl;
  };
} // ns provider


#endif