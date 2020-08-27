
pipeline {
	agent { label 'CI-W10-Slave'}
	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
	stages {
        stage('Build') {
            steps {
                bat 'dir'
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'MSYS', generator: "CodeBlocks - MinGW Makefiles", steps: [[withCmake: true]]
            }
            post {
                success {
                    bat 'dir'
                    archiveArtifacts 'Notch.exe'
                }
                always {
                    cleanWs()
                }
            }
        }
	}
}