// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2009-2016 Illumina, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/// \file

/// \author Chris Saunders
///
#ifndef __BLT_STREAMS_HH
#define __BLT_STREAMS_HH

#include "blt_common/blt_shared.hh"
#include "blt_util/bam_util.hh"
#include "blt_util/prog_info.hh"

#include <iosfwd>
#include <memory>
#include <string>


struct blt_streams {

    blt_streams(const blt_options& client_opt,
                const prog_info& pinfo,
                const bool is_include_seq_name=false);

    ~blt_streams();

    std::ostream* report_osptr() const { return _report_osptr.get(); }
    std::ostream* counts_osptr() const { return _counts_osptr.get(); }
    std::ostream* bsnp_diploid_osptr() const { return _bsnp_diploid_osptr.get(); }
    std::ostream* bsnp_diploid_allele_osptr() const { return _bsnp_diploid_allele_osptr.get(); }
    std::ostream* nonref_test_osptr() const { return _nonref_test_osptr.get(); }
    std::ostream* nonref_sites_osptr() const { return _nonref_sites_osptr.get(); }

protected:

    static
    void
    open_ofstream(const prog_info& pinfo,
                  const std::string& filename,
                  const char* label,
                  const bool is_clobber,
                  std::ofstream& fos);

    // write first few meta-data lines for a legacy blt/starling
    // variant output file:
    //
    static
    void
    write_file_audit(const blt_options& opt,
                     const prog_info& pinfo,
                     const char* const cmdline,
                     std::ostream& os);

    // write the first few meta-data lines for a vcf file:
    //
    static
    void
    write_vcf_audit(const blt_options& opt,
                    const prog_info& pinfo,
                    const char* const cmdline,
                    const bam_header_t* const header,
                    std::ostream& os);

private:
    std::auto_ptr<std::ostream> _report_osptr;
    std::auto_ptr<std::ostream> _counts_osptr;
    std::auto_ptr<std::ostream> _bsnp_diploid_osptr;
    std::auto_ptr<std::ostream> _bsnp_diploid_allele_osptr;
    std::auto_ptr<std::ostream> _nonref_test_osptr;
    std::auto_ptr<std::ostream> _nonref_sites_osptr;
};


#endif
