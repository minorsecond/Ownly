
pipeline {
	agent { label 'CI-W10-Agent'}
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
                ctest installation: 'InSearchPath', workingDir: 'artifacts/', arguments: '--no-compress-output'
                bat 'dir artifacts\\Testing'
                archiveArtifacts (artifacts: 'artifacts/Testing/**/*.xml', fingerprint: true)
                xunit (
                    testTimeMargin: '3000',
                    thresholdMode: 1,
                    thresholds: [
                        skipped(failureThreshold: '0'),
                        failed(failureThreshold: '0')
                    ],
                tools: [CTest(
                    pattern: 'artifacts/Testing/**/*.xml',
                    deleteOutputFiles: true,
                    failIfNotNew: false,
                    skipNoTestFiles: true,
                    stopProcessingIfError: true
                )]
                )
            }
            post {
                failure {
                    cleanWs()
                }
            }
        }
        stage('Archive') {
            steps {
                bat 'del /F/Q/S artifacts\\CMakeFiles'
                bat 'del /F/Q/S artifacts\\database_functions_test_autogen'
                bat 'del /F/Q/S artifacts\\Ownly_autogen'
                bat 'del /F/Q/S artifacts\\src'
                bat 'del /F/Q/S artifacts\\database_functions_test_autogen'
                archiveArtifacts artifacts: 'artifacts/**/**', excludes: "artifacts/Testing/**,artifacts/*.cmake, artifacts/*.tcl,artifacts/*CMake*,artifacts/*autogen*,artifacts/Makefile,artifacts/*cbp,artifacts/database_functions_test.exe"
            }
            post {
                always {
                    cleanWs()
                }
            }
        }
	}
}