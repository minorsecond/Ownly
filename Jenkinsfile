
pipeline {
	agent { label 'CI-W10-Slave'}
	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
	stages {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'MSYS', buildDir: 'artifacts', generator: "CodeBlocks - MinGW Makefiles", steps: [[withCmake: true]]
                bat 'dir'
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Test') {
            steps {
                ctest 'InSearchPath'
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Archive') {
            steps {
                bat 'dir'
                archiveArtifacts artifacts: 'artifacts/*'
            }
            post {
                always {
                    cleanWs()
                }
            }
        }
	}
}