
pipeline {
	agent { label 'CI-W10-Slave'}
	options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
	parameters {
	    booleanParam name: 'RUN_TESTS', defaultValue: true, description: 'Run Tests?'
	}
	stages {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'MSYS', generator: "CodeBlocks - MinGW Makefiles", steps: [[withCmake: true]]
                bat 'dir'
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Test') {
            when {
                environment name: 'RUN_TESTS', value: 'true'
            }
            steps {
            ctest 'InSearchPath'
            }
            post {
                success {
                    archiveArtifacts artifacts: 'Ownly.exe'
                    cleanWs()
                }
                failure {
                    cleanWs()
                }
            }
        }
	}
}