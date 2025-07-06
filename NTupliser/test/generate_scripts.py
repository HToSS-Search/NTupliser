import os

def list_files(m,ct,directory, extension_filter=None):
    files = []
    for entry in os.listdir(directory):
        # print(m,ct)
        # if ('mS'+m in entry) and ('ctauS'+ct in entry):
        #     print(entry)
        if ('_mS'+m+'_' not in entry) or ('_ctauS'+ct+'_' not in entry):
            # print("enters")
            continue
        full_path = os.path.join(directory, entry)
        if os.path.isfile(full_path):
            if (extension_filter is None or entry.endswith(extension_filter)):
                files.append(full_path)
    return files

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="List all files in a directory.")
    parser.add_argument("--in",dest="directory", help="Directory to list files from.")
    parser.add_argument("--ext", help="Optional file extension filter (e.g., .root)", default=None)
    parser.add_argument("--out", help="Directory to list files to", default=None)
    # input='/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/MINIAODSIM/VBF_HToSSTo2Mu2Hadrons_MH125_TuneCP2_13TeV-powheg-pythia8'
    # output='/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/nTuples/VBF_HToSSTo2Mu2Hadrons_MH125_TuneCP2_13TeV-powheg-pythia8'
    args = parser.parse_args()
    mS=['0.4','0.6','0.8','0.9','1','1.1','1.2','1.4','1.6','1.8','2']
    # mS=['2']
    ctau=['0','1','10','100']
    # ctau=['0']
    for m in mS:
        for ct in ctau:
            files = list_files(m,ct,args.directory,args.ext)
            fsh=open('VBF_production/nTuples_VBF_'+'mS'+m+'_ctauS'+ct+'.sh','w')
            # os.makedirs('')
            for i,f in enumerate(files):
                fno=f.split('/')[-1].split('_')[-1].replace('.root','')
                line='cmsRun nTupliser_miniAOD_cfg_local.py inputFiles=file:'+f+' maxEvents=-1'+' outputFile='+os.path.join(args.out,'ntuple_vbf_2017_mS'+m+'_ctauS'+ct+'_'+fno+'.root')
                fsh.write(line)
                fsh.write('\n')
            fsh.close()


    
    # for f in files:
    #     print(f"file:{f}")