import json, shutil
import gitpicker as gp

jdata = json.load(open('.gitpicker.json'))
for files in jdata:
    remote_files = {
        'file': [
            f'{files["root"]}/{f}' for f in files['file']
        ],
        'dir': files['dir'],
    }
    user = files['user']
    repo = files['repo']
    branch = files['branch']
    picker = gp.GitHub(user, repo, branch, remote_files)
    picker.pick()

    for src, des in zip(remote_files['file'], files['file']):
        shutil.move(f'{repo}/{src}', des)
