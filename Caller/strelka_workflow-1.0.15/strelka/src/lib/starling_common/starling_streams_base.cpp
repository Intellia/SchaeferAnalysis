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

#include "blt_util/bam_dumper.hh"
#include "starling_common/starling_streams_base.hh"

#include <cassert>

#include <fstream>
#include <iostream>



std::ostream*
starling_streams_base::
initialize_bindel_file(const starling_options& opt,
                       const prog_info& pinfo,
                       const std::string& filename,
                       const char* label) {

    const char* const cmdline(opt.cmdline.c_str());

    std::ofstream* fosptr(new std::ofstream);
    std::ofstream& fos(*fosptr);
    open_ofstream(pinfo,filename,"bindel-diploid",opt.is_clobber,fos);

    fos << "# ** " << pinfo.name();
    if (label) fos << " " << label;
    fos << " bindel-diploid file **\n";
    write_file_audit(opt,pinfo,cmdline,fos);
    fos << "#$ INDEL_THETA " << opt.bindel_diploid_theta << "\n";
    fos << "#\n";
    fos << "#$ COLUMNS seq_name pos type ref_upstream ref/indel ref_downstream Q(indel) max_gtype Q(max_gtype) depth alt_reads indel_reads other_reads repeat_unit ref_repeat_count indel_repeat_count\n";

    return fosptr;
}



std::ostream*
starling_streams_base::
initialize_gvcf_file(const starling_options& opt,
                     const prog_info& pinfo,
                     const std::string& filename,
                     const bam_header_t* const header,
                     std::auto_ptr<std::ostream>& os_ptr_auto) {

    std::ostream* osptr(&std::cout);
    if (filename != "-") {
        std::ofstream* fos_ptr(new std::ofstream);
        open_ofstream(pinfo,filename,"gvcf",opt.is_clobber,*fos_ptr);
        os_ptr_auto.reset(fos_ptr);
        osptr=os_ptr_auto.get();
    }
    std::ostream& os(*osptr);

    if (! opt.gvcf.is_skip_header) {
        const char* const cmdline(opt.cmdline.c_str());

        write_vcf_audit(opt,pinfo,cmdline,header,os);

        os << "##content=" << pinfo.name() << " small-variant calls\n"
           << "##SnvTheta=" << opt.bsnp_diploid_theta << "\n"
           << "##IndelTheta=" << opt.bindel_diploid_theta << "\n";
    }
    return osptr;
}



bam_dumper*
starling_streams_base::
initialize_realign_bam(const bool is_clobber,
                       const prog_info& pinfo,
                       const std::string& filename,
                       const char* label,
                       const bam_header_t* const header) {

    assert(NULL != header);

    // \TODO consider putting extra info into BAM header:
    //
    //fp->header = bam_header_dup((const bam_header_t*)aux);
    //fos << "@PG\tID:" << pinfo.name() << "\tVN:" << pinfo.version() << "\tCL:" << cmdline << "\n";

    if (not is_clobber) { // weak clobber test:
        std::ofstream fos;
        open_ofstream(pinfo,filename,label,is_clobber,fos);
    }
    return new bam_dumper(filename.c_str(),header);
}



std::ostream*
starling_streams_base::
initialize_candidate_indel_file(const starling_options& opt,
                                const prog_info& pinfo,
                                const std::string& filename) {

    const char* const cmdline(opt.cmdline.c_str());

    std::ofstream* fosptr(new std::ofstream);
    std::ofstream& fos(*fosptr);
    open_ofstream(pinfo,filename,"candidate-indel",opt.is_clobber,fos);

    fos << "# ** " << pinfo.name();
    fos << " candidate-indel file **\n";
    write_file_audit(opt,pinfo,cmdline,fos);
    fos << "#\n";
    fos << "#$ COLUMNS seq_name pos type length seq\n";

    return fosptr;
}



std::ostream*
starling_streams_base::
initialize_window_file(const starling_options& opt,
                       const prog_info& pinfo,
                       const avg_window_data& awd,
                       const sample_info& si) {

    const char* const cmdline(opt.cmdline.c_str());

    std::ofstream* fosptr(new std::ofstream);
    std::ofstream& fos(*fosptr);
    open_ofstream(pinfo,awd.filename,"variant-window",opt.is_clobber,fos);

    const unsigned fs(awd.flank_size);

    fos << "# ** " << pinfo.name();
    fos << " variant-window file **\n";
    write_file_audit(opt,pinfo,cmdline,fos);
    fos << "#$ FLANK_SIZE " << awd.flank_size << "\n";
    fos << "#\n";
    fos << "#$ COLUMNS seq_name pos";
    static const bool is_tier1(true);
    static const char* win_type[] = {"used","filt","submap"};
    static unsigned n_win_type(sizeof(win_type)/sizeof(char*));
    const unsigned n_samples(si.sample_size());
    for (unsigned s(0); s<n_samples; ++s) {
        for (unsigned i(0); i<n_win_type; ++i) {
            fos << " " << si.get_prefix(s,is_tier1) << "win" << fs << "_" << win_type[i];
        }
    }
    fos << "\n";

    return fosptr;
}



starling_streams_base::
starling_streams_base(const starling_options& opt,
                      const prog_info& pinfo,
                      const sample_info& si)
    : base_t(opt,pinfo,true)
    , _n_samples(si.sample_size())
    , _window_osptr(opt.variant_windows.size())
{
    assert((_n_samples>0) && (_n_samples<=MAX_SAMPLE));

    for (unsigned i(0); i<_n_samples; ++i) _gvcf_osptr[i] = NULL;

    if (opt.is_write_candidate_indels()) {
        _candidate_indel_osptr.reset(initialize_candidate_indel_file(opt,pinfo,opt.candidate_indel_filename));
    }

    const unsigned vs(opt.variant_windows.size());
    for (unsigned i(0); i<vs; ++i) {
        _window_osptr[i].reset(initialize_window_file(opt,pinfo,opt.variant_windows[i],si));
    }
}



// dtor here to make auto_ptr work correctly:
starling_streams_base::
~starling_streams_base() {}
