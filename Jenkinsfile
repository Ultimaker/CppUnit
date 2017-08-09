parallel_nodes(["linux && cura", "windows && cura"]) {
    stage('Prepare') {
        step([$class: 'WsCleanup'])

        checkout scm
    }

    catchError {
        dir('build') {
            stage('Build') {
                def branch = env.BRANCH_NAME
                if(!(branch =~ /^2.\d+$/)) {
                    branch = "master"
                }

                cmake '..', "-DCMAKE_PREFIX_PATH=\"${env.CURA_ENVIRONMENT_PATH}/${branch}\" -DCMAKE_BUILD_TYPE=Release"
                make ''
            }
        }
    }

    stage('Finalize') {
    }
}
