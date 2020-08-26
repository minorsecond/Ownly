
pipeline {
	agent { label 'CI-W10-Slave'}
	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
	stages {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'MSYS', steps: [[withCmake: true]]
            }
            post {
                success {
                    archiveArtifacts 'Notch.exe'
                }
                always {
                    cleanWs()
                }
            }
        }
	}
}